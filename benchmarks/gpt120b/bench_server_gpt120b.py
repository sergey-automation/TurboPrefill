import csv
import os
import re
import signal
import subprocess
import threading
import time
from datetime import datetime
from pathlib import Path

import requests

CONFIG_PATH = "server_config_gpt120b.sh"
SERVER_READY_TIMEOUT_S = 920
REQUEST_TIMEOUT_S = 3600

# GPU load separation between prefill/decode stages is approximate.
# Stage boundaries are estimated from llama-server timing fields:
#   prompt_ms    -> prefill
#   predicted_ms -> decode
# The goal is comparative benchmarking, not cycle-accurate GPU profiling.


def load_cfg(path=CONFIG_PATH):
    cfg = {}
    text = Path(path).read_text(encoding="utf-8")

    for line in text.splitlines():
        line = line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue

        key, value = line.split("=", 1)
        cfg[key.strip()] = os.path.expandvars(value.strip().strip('"').strip("'"))

    defaults = {
        "MODEL": "$HOME/workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf",
        "CONTEXTS_DIR": "$HOME/workspace/projects/llama.cpp/contexts_gpt_tokenizer",
        "OUTPUT_DIR": "$HOME/workspace/projects/llama.cpp/bench_reports_gpt-120b",
        "HOST": "127.0.0.1",
        "PORT": "8081",
        "NGL": "99",
        "CTX_SIZE": "17002",
        "N_GEN": "128",
        "BATCH": "512",
        "UBATCH": "512",
        "PARALLEL": "2",
        "CTK": "f16",
        "SPLIT_MODE": "layer",
        "TENSOR_SPLIT": "3/3/4/4/4/4/4/4/3/3",
        "TEMPERATURE": "0.0",
        "MONITOR_INTERVAL": "0.2",
        "GGML_SCHED_DEBUG": "0",
        "GGML_CUDA_DEBUG": "0",
    }

    for key, value in defaults.items():
        cfg.setdefault(key, os.path.expandvars(value))

    return cfg


cfg = load_cfg()


def nvidia_sample():
    out = subprocess.check_output([
        "nvidia-smi",
        "--query-gpu=index,name,pci.bus_id,pcie.link.gen.current,pcie.link.width.current,utilization.gpu,power.draw,memory.used",
        "--format=csv,noheader,nounits",
    ], text=True)

    rows = []
    for line in out.strip().splitlines():
        parts = [x.strip() for x in line.split(",")]
        rows.append({
            "gpu": int(parts[0]),
            "name": parts[1],
            "bus": parts[2],
            "gen": parts[3],
            "width": parts[4],
            "util": float(parts[5]),
            "power": float(parts[6]),
            "mem": float(parts[7]),
            "t": time.time(),
        })
    return rows


class Monitor:
    def __init__(self, interval):
        self.interval = float(interval)
        self.samples = []
        self.stop_flag = False
        self.thread = threading.Thread(target=self.run, daemon=True)

    def start(self):
        self.thread.start()

    def stop(self):
        self.stop_flag = True
        self.thread.join(timeout=2)

    def run(self):
        while not self.stop_flag:
            try:
                self.samples.extend(nvidia_sample())
            except Exception:
                pass
            time.sleep(self.interval)


def avg_gpu(samples, t0, t1):
    selected = [s for s in samples if t0 <= s["t"] <= t1]
    out = {}

    for gpu in sorted(set(s["gpu"] for s in selected)):
        gpu_samples = [s for s in selected if s["gpu"] == gpu]
        if not gpu_samples:
            continue

        out[gpu] = {
            "name": gpu_samples[-1]["name"],
            "pcie": f"Gen{gpu_samples[-1]['gen']} x{gpu_samples[-1]['width']}",
            "util_avg": sum(x["util"] for x in gpu_samples) / len(gpu_samples),
            "util_max": max(x["util"] for x in gpu_samples),
            "power_avg": sum(x["power"] for x in gpu_samples) / len(gpu_samples),
            "power_max": max(x["power"] for x in gpu_samples),
            "mem_max": max(x["mem"] for x in gpu_samples),
            "samples": len(gpu_samples),
        }

    return out


def fmt(value, nd=2):
    if value is None:
        return "n/a"
    try:
        return f"{float(value):.{nd}f}"
    except Exception:
        return str(value)


def start_server(out_dir):
    subprocess.run("pkill -f llama-server || true", shell=True)

    log_path = out_dir / "llama_server.log"
    log = open(log_path, "w", encoding="utf-8")

    cmd = [
        "./build/bin/llama-server",
        "-m", cfg["MODEL"],
        "--host", cfg["HOST"],
        "--port", str(cfg["PORT"]),
        "-ngl", str(cfg["NGL"]),
        "-c", str(cfg["CTX_SIZE"]),
        "-b", str(cfg["BATCH"]),
        "-ub", str(cfg["UBATCH"]),
        "-np", str(cfg["PARALLEL"]),
        "-ctk", cfg["CTK"],
        "-sm", cfg["SPLIT_MODE"],
        "-ts", cfg["TENSOR_SPLIT"],
    ]

    env = os.environ.copy()
    env["GGML_SCHED_DEBUG"] = cfg.get("GGML_SCHED_DEBUG", "0")

    if cfg.get("GGML_CUDA_DEBUG", "0") != "0":
        env["GGML_CUDA_DEBUG"] = cfg["GGML_CUDA_DEBUG"]

    proc = subprocess.Popen(
        cmd,
        stdout=log,
        stderr=subprocess.STDOUT,
        text=True,
        env=env,
    )

    url = f"http://{cfg['HOST']}:{cfg['PORT']}/v1/models"
    for _ in range(SERVER_READY_TIMEOUT_S):
        if proc.poll() is not None:
            log.close()
            tail = log_path.read_text(encoding="utf-8", errors="ignore").splitlines()[-80:]
            raise RuntimeError("llama-server exited during startup. Last log lines:\n" + "\n".join(tail))

        try:
            response = requests.get(url, timeout=2)
            if response.status_code == 200:
                return proc, log_path, cmd
        except Exception:
            pass

        time.sleep(1)

    proc.terminate()
    log.close()
    raise RuntimeError(f"llama-server did not start within {SERVER_READY_TIMEOUT_S} seconds. Log: {log_path}")


def request_one(prompt):
    url = f"http://{cfg['HOST']}:{cfg['PORT']}/completion"
    payload = {
        "prompt": prompt,
        "n_predict": int(cfg["N_GEN"]),
        "temperature": float(cfg["TEMPERATURE"]),
        "top_k": 1,
        "top_p": 1.0,
        "min_p": 0.0,
        "cache_prompt": False,
        "stream": False,
    }

    t0 = time.time()
    response = requests.post(url, json=payload, timeout=REQUEST_TIMEOUT_S)
    t1 = time.time()
    response.raise_for_status()

    return t0, t1, response.json()


def prompt_size_from_name(path):
    match = re.search(r"ctx_(?:\d+_)?(\d+)", path.name)
    return int(match.group(1)) if match else 0


def collect_environment():
    info = {
        "TURBOPREFILL": os.environ.get("TURBOPREFILL", "0"),
    }

    commands = {
        "nvidia_smi": ["nvidia-smi", "--query-gpu=index,name,driver_version,memory.total", "--format=csv,noheader"],
        "nvcc": ["nvcc", "--version"],
        "cmake": ["cmake", "--version"],
    }

    for key, cmd in commands.items():
        try:
            info[key] = subprocess.check_output(cmd, text=True, stderr=subprocess.STDOUT).strip()
        except Exception as exc:
            info[key] = f"unavailable: {exc}"

    return info


def write_report(report, raw_csv, results, server_log, server_cmd, env_info):
    with open(raw_csv, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["file", "prompt_tokens", "completion_tokens", "prefill_ms", "prefill_tok_s", "decode_ms", "decode_tok_s", "wall_ms"])
        for row in results:
            writer.writerow([
                row["file"],
                row["prompt_tokens"],
                row["completion_tokens"],
                row["prefill_ms"],
                row["prefill_tps"],
                row["decode_ms"],
                row["decode_tps"],
                row["wall_ms"],
            ])

    with open(report, "w", encoding="utf-8") as f:
        f.write("# llama-server context benchmark report\n\n")

        f.write("## Test header\n\n")
        for key in ["MODEL", "NGL", "CTX_SIZE", "N_GEN", "BATCH", "UBATCH", "CTK", "SPLIT_MODE", "TENSOR_SPLIT", "PARALLEL", "TEMPERATURE"]:
            f.write(f"- {key}: `{cfg[key]}`\n")
        f.write(f"- TURBOPREFILL: `{env_info['TURBOPREFILL']}`\n")
        f.write(f"- llama_server_log: `{server_log}`\n\n")

        f.write("## Environment\n\n")
        for key, value in env_info.items():
            f.write(f"### {key}\n\n```text\n{value}\n```\n\n")

        f.write("## Server command\n\n```bash\n")
        f.write(" ".join(server_cmd))
        f.write("\n```\n\n")

        f.write("## Summary\n\n")
        f.write("| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |\n")
        f.write("|---|---:|---:|---:|---:|---:|---:|\n")
        for row in results:
            f.write(
                f"| {row['file']} "
                f"| {row['prompt_tokens']} "
                f"| {row['completion_tokens']} "
                f"| {fmt(row['prefill_tps'])} "
                f"| {fmt(row['prefill_ms'] / 1000.0)} "
                f"| {fmt(row['decode_tps'])} "
                f"| {fmt(row['wall_ms'] / 1000.0)} |\n"
            )

        f.write("\n## GPU load by stage\n\n")
        for row in results:
            f.write(f"### {row['file']}\n\n")
            for stage_name, samples in [("Prefill", row["pre"]), ("Decode", row["dec"] )]:
                f.write(f"{stage_name} stage:\n\n")
                f.write("| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |\n")
                f.write("|---:|---|---|---:|---:|---:|---:|---:|\n")
                for gpu, sample in samples.items():
                    f.write(
                        f"| {gpu} | {sample['name']} | {sample['pcie']} "
                        f"| {fmt(sample['util_avg'], 1)} | {fmt(sample['util_max'], 1)} "
                        f"| {fmt(sample['power_avg'], 1)} | {fmt(sample['power_max'], 1)} "
                        f"| {fmt(sample['mem_max'], 0)} |\n"
                    )
                f.write("\n")


def main():
    out_dir = Path(cfg["OUTPUT_DIR"]) / datetime.now().strftime("%Y%m%d_%H%M%S")
    out_dir.mkdir(parents=True, exist_ok=True)

    report = out_dir / "report.md"
    raw_csv = out_dir / "raw_results.csv"
    env_info = collect_environment()

    server, server_log, server_cmd = start_server(out_dir)

    ctx_files = sorted(Path(cfg["CONTEXTS_DIR"]).glob("ctx_*.txt"), key=prompt_size_from_name)
    if not ctx_files:
        server.send_signal(signal.SIGINT)
        raise RuntimeError(f"No ctx_*.txt files found in {cfg['CONTEXTS_DIR']}")

    results = []

    try:
        for ctx in ctx_files:
            text = ctx.read_text(encoding="utf-8", errors="ignore")
            monitor = Monitor(cfg["MONITOR_INTERVAL"])
            monitor.start()

            t0, t1, data = request_one(text)
            monitor.stop()

            timings = data.get("timings", {})
            usage = data.get("usage", {})

            prompt_ms = float(timings.get("prompt_ms", 0))
            decode_ms = float(timings.get("predicted_ms", 0))
            prefill_tps = float(timings.get("prompt_per_second", 0))
            decode_tps = float(timings.get("predicted_per_second", 0))

            prompt_tokens = usage.get("prompt_tokens") or data.get("tokens_evaluated")
            completion_tokens = usage.get("completion_tokens") or data.get("tokens_predicted")
            total_tokens = usage.get("total_tokens")
            if total_tokens is None and prompt_tokens is not None and completion_tokens is not None:
                total_tokens = prompt_tokens + completion_tokens

            pre_t0 = t0
            pre_t1 = t0 + prompt_ms / 1000.0
            dec_t0 = pre_t1
            dec_t1 = t1

            row = {
                "file": ctx.name,
                "prompt_target": prompt_size_from_name(ctx),
                "prompt_tokens": prompt_tokens,
                "completion_tokens": completion_tokens,
                "total_tokens": total_tokens,
                "prefill_ms": prompt_ms,
                "prefill_tps": prefill_tps,
                "decode_ms": decode_ms,
                "decode_tps": decode_tps,
                "wall_ms": (t1 - t0) * 1000.0,
                "pre": avg_gpu(monitor.samples, pre_t0, pre_t1),
                "dec": avg_gpu(monitor.samples, dec_t0, dec_t1),
            }
            results.append(row)

            print(f"{ctx.name}: prefill={prefill_tps:.2f} tok/s decode={decode_tps:.2f} tok/s")

    finally:
        try:
            server.send_signal(signal.SIGINT)
        except Exception:
            pass

    write_report(report, raw_csv, results, server_log, server_cmd, env_info)

    print("REPORT:", report)
    print("CSV:", raw_csv)


if __name__ == "__main__":
    main()

