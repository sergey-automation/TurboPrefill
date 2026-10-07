#!/usr/bin/env python3

import csv
import hashlib
import json
import os
import re
import shlex
import signal
import statistics
import subprocess
import sys
import threading
import time
from collections import Counter
from datetime import datetime
from pathlib import Path

import requests

CONFIG_NAME = "config_Qwen_3.8.sh"
SCRIPT_DIR = Path(__file__).resolve().parent
RUN_DIR = Path.cwd().resolve()

# v3 timing policy:
#   1) Keep llama-server timings exactly as reported:
#        prompt_ms / prompt_per_second
#        predicted_ms / predicted_per_second
#   2) Independently measure from the client:
#        client_prefill_ms ~= request start -> first streamed output token
#        client_decode_ms  ~= first streamed output token -> full response received
#        client_wall_ms    = request start -> full response received
#      This client split is intentionally an end-to-end measurement and includes
#      small HTTP/streaming overhead. It is independent of llama-server timing fields.
#
# Parallel-slots mode:
#   PARALLEL=N means llama-server is started with exactly N slots (-np N).
#   For every ctx_*.txt file, exactly N identical requests are submitted concurrently,
#   one request per slot. The next context is NOT started until all N responses finish.
#   There is no active_slots=1..PARALLEL sweep.


def bool_cfg(value, default=False):
    if value is None or str(value).strip() == "":
        return default
    return str(value).strip().lower() in {"1", "true", "yes", "on", "enabled"}


def safe_float(value):
    try:
        return float(value)
    except (TypeError, ValueError):
        return None


def fmt(value, nd=2):
    if value is None:
        return "n/a"
    try:
        return f"{float(value):.{nd}f}"
    except Exception:
        return str(value)


def run_text(cmd, cwd=None, env=None, timeout=15):
    try:
        return subprocess.check_output(
            cmd,
            text=True,
            stderr=subprocess.STDOUT,
            cwd=cwd,
            env=env,
            timeout=timeout,
        ).strip()
    except Exception as exc:
        return f"unavailable: {exc}"


def find_config_path():
    p = RUN_DIR / CONFIG_NAME
    if p.is_file():
        return p
    p = SCRIPT_DIR / CONFIG_NAME
    if p.is_file():
        return p
    raise FileNotFoundError(
        f"{CONFIG_NAME} not found in current directory ({RUN_DIR}) "
        f"or beside the script ({SCRIPT_DIR})"
    )


def load_cfg():
    path = find_config_path()

    # Source the .sh through bash instead of partially reimplementing shell syntax.
    # This preserves $PWD, ${VAR:-default}, quotes, and BASH_SOURCE behavior.
    command = 'set -a; source "$1"; env -0'
    raw = subprocess.check_output(
        ["bash", "-c", command, "bench-config", str(path)],
        cwd=str(RUN_DIR),
    )

    cfg = {}
    for item in raw.split(b"\0"):
        if not item or b"=" not in item:
            continue
        key, value = item.split(b"=", 1)
        cfg[key.decode(errors="replace")] = value.decode(errors="replace")

    defaults = {
        "MODEL": "",
        "MMPROJ": "",
        "CONTEXTS_DIR": str(RUN_DIR / "contexts_llama3_70b"),
        "OUTPUT_DIR": str(RUN_DIR / "bench_reports_Qwen3.8-27B-Q8_0"),
        "HOST": "0.0.0.0",
        "PORT": "8081",
        "NGL": "999",
        "CTX_SIZE": "200000",
        "N_GEN": "128",
        "BATCH": "4097",
        "UBATCH": "32",
        "PARALLEL": "1",
        "CTK": "f16",
        "CTV": "f16",
        "SPEC_TYPE": "none",
        "SPEC_DRAFT_N_MAX": "4",
        "SPEC_DRAFT_MODEL": "",
        "SPEC_EXTRA_ARGS": "",
        "SPLIT_MODE": "layer",
        "TENSOR_SPLIT": "",
        "CUDA_VISIBLE_DEVICES": "",
        "TEMPERATURE": "0.15",
        "MONITOR_INTERVAL": "2",
        "GGML_SCHED_DEBUG": "0",
        "GGML_CUDA_DEBUG": "0",
        "LLAMA_SERVER_BIN": str(RUN_DIR / "build/bin/llama-server"),
        "LOCAL_LD_LIBRARY_PATH": str(RUN_DIR / "build/bin"),
        "UNSET_LD_PRELOAD": "1",
        "TURBOPREFILL": "0",
        "LOG_LEVEL": "4",
        "CACHE_PROMPT": "0",
        "WARMUP": "1",
        "WARMUP_MAX_TOKENS": "9000",
        "LLAMA_BUILTIN_WARMUP": "0",
        "KEEP_SERVER_RUNNING": "1",
        "REPEATS": "1",
        "FLASH_ATTN": "auto",
        "THREADS": "auto",
        "THREADS_BATCH": "auto",
        "MODEL_HASH": "0",
        "MMPROJ_OFFLOAD": "1",
        "MTMD_BACKEND_DEVICE": "",
        "SERVER_READY_TIMEOUT_S": "2400",
        "REQUEST_TIMEOUT_S": "3600",
    }
    for key, value in defaults.items():
        cfg.setdefault(key, value)

    cfg["CONFIG_PATH"] = str(path)
    return cfg


cfg = load_cfg()
SERVER_READY_TIMEOUT_S = int(cfg["SERVER_READY_TIMEOUT_S"])
REQUEST_TIMEOUT_S = int(cfg["REQUEST_TIMEOUT_S"])


def split_count(value):
    parts = [x for x in re.split(r"[/,;\s]+", str(value).strip()) if x]
    return len(parts)


def query_gpu_inventory():
    out = subprocess.check_output([
        "nvidia-smi",
        "--query-gpu=index,name,pci.bus_id,memory.total,driver_version,pcie.link.gen.current,pcie.link.width.current",
        "--format=csv,noheader,nounits",
    ], text=True)

    rows = []
    for line in out.strip().splitlines():
        p = [x.strip() for x in line.split(",")]
        if len(p) < 7:
            continue
        rows.append({
            "index": int(p[0]),
            "name": p[1],
            "bus": p[2],
            "memory_total_mib": safe_float(p[3]),
            "driver": p[4],
            "gen": p[5],
            "width": p[6],
        })
    return rows


def parse_cuda_devices(value):
    value = str(value or "").strip()
    if not value:
        return []
    parts = [x.strip() for x in value.split(",") if x.strip()]
    if any(not x.isdigit() for x in parts):
        raise ValueError(
            "This benchmark currently expects numeric CUDA_VISIBLE_DEVICES indices, "
            f"got: {value!r}"
        )
    return [int(x) for x in parts]


def resolve_selected_gpus(inventory):
    physical_ids = [g["index"] for g in inventory]
    requested = parse_cuda_devices(cfg.get("CUDA_VISIBLE_DEVICES", ""))
    n_split = split_count(cfg.get("TENSOR_SPLIT", ""))
    required = max(len(requested), n_split)

    if required == 0:
        return requested
    if required > len(physical_ids):
        raise RuntimeError(
            f"Need {required} visible GPUs from CUDA_VISIBLE_DEVICES/TENSOR_SPLIT, "
            f"but nvidia-smi reports only {len(physical_ids)}"
        )

    selected = list(requested)
    for gpu_id in physical_ids:
        if len(selected) >= required:
            break
        if gpu_id not in selected:
            selected.append(gpu_id)

    missing = [x for x in selected if x not in physical_ids]
    if missing:
        raise RuntimeError(f"CUDA_VISIBLE_DEVICES references missing GPU indices: {missing}")

    return selected


GPU_INVENTORY = query_gpu_inventory()
SELECTED_GPU_IDS = resolve_selected_gpus(GPU_INVENTORY)
EFFECTIVE_CUDA_VISIBLE_DEVICES = ",".join(str(x) for x in SELECTED_GPU_IDS)


def selected_gpu_summary():
    by_id = {g["index"]: g for g in GPU_INVENTORY}
    names = [by_id[x]["name"] for x in SELECTED_GPU_IDS if x in by_id]
    counts = Counter(names)
    summary = "; ".join(
        f"{name} x{count}" for name, count in sorted(counts.items())
    )
    return len(names), summary


SELECTED_GPU_COUNT, SELECTED_GPU_MODELS = selected_gpu_summary()


def nvidia_sample(selected_ids=None):
    out = subprocess.check_output([
        "nvidia-smi",
        "--query-gpu=index,name,pci.bus_id,pcie.link.gen.current,pcie.link.width.current,utilization.gpu,power.draw,memory.used",
        "--format=csv,noheader,nounits",
    ], text=True)

    wanted = None if selected_ids is None else set(selected_ids)
    now = time.time()
    rows = []
    for line in out.strip().splitlines():
        parts = [x.strip() for x in line.split(",")]
        if len(parts) < 8:
            continue
        idx = int(parts[0])
        if wanted is not None and idx not in wanted:
            continue
        rows.append({
            "gpu": idx,
            "name": parts[1],
            "bus": parts[2],
            "gen": parts[3],
            "width": parts[4],
            "util": safe_float(parts[5]),
            "power": safe_float(parts[6]),
            "mem": safe_float(parts[7]),
            "t": now,
        })
    return rows


def read_cpu_times():
    out = []
    with open("/proc/stat", "r", encoding="utf-8") as f:
        for line in f:
            if not line.startswith("cpu"):
                break
            parts = line.split()
            name = parts[0]
            if name != "cpu" and not name[3:].isdigit():
                continue
            vals = [int(x) for x in parts[1:]]
            vals += [0] * max(0, 8 - len(vals))
            user, nice, system, idle, iowait, irq, softirq, steal = vals[:8]
            total = user + nice + system + idle + iowait + irq + softirq + steal
            idle_all = idle + iowait
            out.append((total, idle_all))
    return out


def cpu_percentages(prev, curr):
    if not prev or not curr:
        return None, []
    values = []
    for (pt, pi), (ct, ci) in zip(prev, curr):
        dt = ct - pt
        di = ci - pi
        if dt <= 0:
            values.append(None)
        else:
            values.append(max(0.0, min(100.0, 100.0 * (dt - di) / dt)))
    if not values:
        return None, []
    return values[0], values[1:]


def read_memory():
    mem = {}
    with open("/proc/meminfo", "r", encoding="utf-8") as f:
        for line in f:
            key, rest = line.split(":", 1)
            value = rest.strip().split()[0]
            mem[key] = int(value)  # KiB

    total = mem.get("MemTotal", 0)
    available = mem.get("MemAvailable", mem.get("MemFree", 0))
    used = max(0, total - available)
    swap_total = mem.get("SwapTotal", 0)
    swap_free = mem.get("SwapFree", 0)
    swap_used = max(0, swap_total - swap_free)

    return {
        "ram_total_mib": total / 1024.0,
        "ram_used_mib": used / 1024.0,
        "ram_available_mib": available / 1024.0,
        "ram_used_pct": (100.0 * used / total) if total else 0.0,
        "swap_total_mib": swap_total / 1024.0,
        "swap_used_mib": swap_used / 1024.0,
        "swap_used_pct": (100.0 * swap_used / swap_total) if swap_total else 0.0,
    }


class Monitor:
    def __init__(self, interval):
        self.interval = max(0.1, float(interval))
        self.gpu_samples = []
        self.system_samples = []
        self.stop_event = threading.Event()
        self.thread = threading.Thread(target=self.run, daemon=True)
        self.prev_cpu = read_cpu_times()

    def start(self):
        self.thread.start()

    def stop(self):
        self.stop_event.set()
        self.thread.join(timeout=max(2.0, self.interval + 1.0))

    def capture(self):
        now = time.time()
        curr_cpu = read_cpu_times()
        cpu_total, cpu_cores = cpu_percentages(self.prev_cpu, curr_cpu)
        self.prev_cpu = curr_cpu
        memory = read_memory()
        try:
            gpu_rows = nvidia_sample(SELECTED_GPU_IDS)
        except Exception:
            gpu_rows = []

        for g in gpu_rows:
            g["t"] = now
        self.gpu_samples.extend(gpu_rows)

        sample = {
            "t": now,
            "cpu_total_pct": cpu_total,
            "cpu_cores_pct": cpu_cores,
            **memory,
            "gpus": gpu_rows,
        }
        self.system_samples.append(sample)

    def run(self):
        while not self.stop_event.is_set():
            try:
                self.capture()
            except Exception:
                pass
            self.stop_event.wait(self.interval)


def valid_numbers(values):
    return [x for x in values if x is not None]


def avg_gpu(samples, t0, t1):
    selected = [s for s in samples if t0 <= s["t"] <= t1]
    out = {}

    for gpu in sorted(set(s["gpu"] for s in selected)):
        gpu_samples = [s for s in selected if s["gpu"] == gpu]
        if not gpu_samples:
            continue

        utils = valid_numbers([x["util"] for x in gpu_samples])
        powers = valid_numbers([x["power"] for x in gpu_samples])
        mems = valid_numbers([x["mem"] for x in gpu_samples])
        out[gpu] = {
            "name": gpu_samples[-1]["name"],
            "pcie": f"Gen{gpu_samples[-1]['gen']} x{gpu_samples[-1]['width']}",
            "util_avg": statistics.mean(utils) if utils else None,
            "util_max": max(utils) if utils else None,
            "power_avg": statistics.mean(powers) if powers else None,
            "power_max": max(powers) if powers else None,
            "mem_max": max(mems) if mems else None,
            "samples": len(gpu_samples),
        }

    return out


def avg_system(samples, t0, t1):
    selected = [s for s in samples if t0 <= s["t"] <= t1]
    if not selected:
        return {}

    cpu_total = valid_numbers([s["cpu_total_pct"] for s in selected])
    max_cores = max((len(s["cpu_cores_pct"]) for s in selected), default=0)
    core_stats = {}
    for i in range(max_cores):
        vals = valid_numbers([
            s["cpu_cores_pct"][i]
            for s in selected
            if i < len(s["cpu_cores_pct"])
        ])
        if vals:
            core_stats[i] = {"avg": statistics.mean(vals), "max": max(vals)}

    def field_stats(key):
        vals = valid_numbers([s.get(key) for s in selected])
        if not vals:
            return {"avg": None, "max": None}
        return {"avg": statistics.mean(vals), "max": max(vals)}

    return {
        "samples": len(selected),
        "cpu_total_avg": statistics.mean(cpu_total) if cpu_total else None,
        "cpu_total_max": max(cpu_total) if cpu_total else None,
        "cores": core_stats,
        "ram_used_mib": field_stats("ram_used_mib"),
        "ram_used_pct": field_stats("ram_used_pct"),
        "swap_used_mib": field_stats("swap_used_mib"),
        "swap_used_pct": field_stats("swap_used_pct"),
    }


def prompt_size_from_name(path):
    match = re.search(r"ctx_(?:\d+_)?(\d+)", path.name)
    return int(match.group(1)) if match else 0


def client_host():
    host = cfg["HOST"].strip()
    if host in {"0.0.0.0", "::", "[::]", ""}:
        return "127.0.0.1"
    return host


def make_server_env():
    env = os.environ.copy()
    tp_mode = env.get("TURBOPREFILL", cfg.get("TURBOPREFILL", "0")).strip()
    env["TURBOPREFILL"] = tp_mode

    local_lib = str(Path(cfg["LOCAL_LD_LIBRARY_PATH"]).expanduser())
    env["LD_LIBRARY_PATH"] = local_lib + (
        ":" + env["LD_LIBRARY_PATH"] if env.get("LD_LIBRARY_PATH") else ""
    )

    if bool_cfg(cfg.get("UNSET_LD_PRELOAD"), True):
        env.pop("LD_PRELOAD", None)

    if EFFECTIVE_CUDA_VISIBLE_DEVICES:
        env["CUDA_VISIBLE_DEVICES"] = EFFECTIVE_CUDA_VISIBLE_DEVICES
    else:
        env.pop("CUDA_VISIBLE_DEVICES", None)

    env["GGML_SCHED_DEBUG"] = cfg.get("GGML_SCHED_DEBUG", "0")
    if cfg.get("GGML_CUDA_DEBUG", "0") != "0":
        env["GGML_CUDA_DEBUG"] = cfg["GGML_CUDA_DEBUG"]
    else:
        env.pop("GGML_CUDA_DEBUG", None)

    if cfg.get("MTMD_BACKEND_DEVICE", "").strip():
        env["MTMD_BACKEND_DEVICE"] = cfg["MTMD_BACKEND_DEVICE"].strip()

    return env


def build_server_command():
    server_bin = str(Path(cfg["LLAMA_SERVER_BIN"]).expanduser())
    cmd = [
        server_bin,
        "-m", cfg["MODEL"],
        "--host", cfg["HOST"],
        "--port", str(cfg["PORT"]),
        "-lv", str(cfg.get("LOG_LEVEL", "4")),
        "-ngl", str(cfg["NGL"]),
        "-c", str(cfg["CTX_SIZE"]),
        "--override-kv", f"llama.context_length=int:{cfg['CTX_SIZE']}",
        "-b", str(cfg["BATCH"]),
        "-ub", str(cfg["UBATCH"]),
        "-np", str(cfg["PARALLEL"]),
        "-ctk", cfg["CTK"],
        "-ctv", cfg["CTV"],
        "-sm", cfg["SPLIT_MODE"],
    ]

    if cfg.get("TENSOR_SPLIT", "").strip():
        cmd += ["-ts", cfg["TENSOR_SPLIT"]]

    flash = cfg.get("FLASH_ATTN", "auto").strip().lower()
    if flash in {"on", "off", "auto"}:
        cmd += ["--flash-attn", flash]

    threads = cfg.get("THREADS", "auto").strip().lower()
    if threads not in {"", "auto", "default", "-1"}:
        cmd += ["--threads", threads]

    threads_batch = cfg.get("THREADS_BATCH", "auto").strip().lower()
    if threads_batch not in {"", "auto", "default", "-1"}:
        cmd += ["--threads-batch", threads_batch]

    # Disable llama.cpp's own empty-run warmup by default. The benchmark has a
    # separate configurable real-context warmup.
    if not bool_cfg(cfg.get("LLAMA_BUILTIN_WARMUP"), False):
        cmd.append("--no-warmup")

    mmproj = cfg.get("MMPROJ", "").strip()
    if mmproj:
        cmd += ["--mmproj", mmproj]
        if not bool_cfg(cfg.get("MMPROJ_OFFLOAD"), True):
            cmd.append("--no-mmproj-offload")
    else:
        # Explicit text-only mode. Both b10335 and b10437 support --no-mmproj.
        cmd.append("--no-mmproj")

    spec_type = cfg.get("SPEC_TYPE", "none").strip()
    if spec_type:
        cmd += ["--spec-type", spec_type]
        if spec_type.lower() != "none":
            if cfg.get("SPEC_DRAFT_N_MAX", "").strip():
                cmd += ["--spec-draft-n-max", cfg["SPEC_DRAFT_N_MAX"].strip()]
            if cfg.get("SPEC_DRAFT_MODEL", "").strip():
                cmd += ["--spec-draft-model", cfg["SPEC_DRAFT_MODEL"].strip()]
            if cfg.get("SPEC_EXTRA_ARGS", "").strip():
                cmd += shlex.split(cfg["SPEC_EXTRA_ARGS"])

    return cmd


def validate_inputs():
    model = Path(cfg["MODEL"]).expanduser()
    if not model.is_file():
        raise FileNotFoundError(f"MODEL not found: {model}")

    server = Path(cfg["LLAMA_SERVER_BIN"]).expanduser()
    if not server.is_file():
        raise FileNotFoundError(f"llama-server not found: {server}")
    if not os.access(server, os.X_OK):
        raise PermissionError(f"llama-server is not executable: {server}")

    mmproj = cfg.get("MMPROJ", "").strip()
    if mmproj and not Path(mmproj).expanduser().is_file():
        raise FileNotFoundError(f"MMPROJ not found: {mmproj}")

    contexts = Path(cfg["CONTEXTS_DIR"]).expanduser()
    if not contexts.is_dir():
        raise FileNotFoundError(f"CONTEXTS_DIR not found: {contexts}")


def listening_pid_for_port(port):
    """Return the single PID listening on TCP port, or None."""
    try:
        out = subprocess.check_output(
            ["ss", "-ltnp", f"sport = :{int(port)}"],
            text=True,
            stderr=subprocess.STDOUT,
        )
    except Exception:
        return None

    pids = sorted(set(int(x) for x in re.findall(r"pid=(\d+)", out)))
    return pids[0] if len(pids) == 1 else None


def stop_existing_server_on_bench_port():
    """Stop only the exact process listening on the configured benchmark port."""
    pid = listening_pid_for_port(cfg["PORT"])
    if pid is None:
        return

    expected = Path(cfg["LLAMA_SERVER_BIN"]).expanduser().resolve()
    try:
        actual = Path(f"/proc/{pid}/exe").resolve()
    except Exception:
        raise RuntimeError(
            f"Port {cfg['PORT']} is already in use by PID {pid}; "
            "cannot verify its executable, so it was not touched."
        )

    if actual != expected:
        raise RuntimeError(
            f"Port {cfg['PORT']} is already in use by PID {pid}: {actual}. "
            f"Expected benchmark server: {expected}. Process was not touched."
        )

    os.kill(pid, signal.SIGINT)
    deadline = time.monotonic() + 20.0
    while time.monotonic() < deadline:
        if not Path(f"/proc/{pid}").exists():
            return
        time.sleep(0.2)

    raise RuntimeError(
        f"Previous benchmark llama-server PID {pid} did not stop after SIGINT."
    )


def start_server(out_dir):
    stop_existing_server_on_bench_port()

    log_path = out_dir / "llama_server.log"
    pid_path = out_dir / "llama_server.pid"
    env = make_server_env()
    cmd = build_server_command()

    with open(log_path, "w", encoding="utf-8") as log:
        log.write(f"BENCH_RUN_DIR      : {RUN_DIR}\n")
        log.write(f"TURBOPREFILL       : {env.get('TURBOPREFILL', '0')}\n")
        log.write(f"MODEL              : {cfg['MODEL']}\n")
        log.write(f"CTX_SIZE           : {cfg['CTX_SIZE']}\n")
        log.write(f"BATCH              : {cfg['BATCH']}\n")
        log.write(f"UBATCH             : {cfg['UBATCH']}\n")
        log.write(f"CUDA_VISIBLE_DEVICES: {EFFECTIVE_CUDA_VISIBLE_DEVICES}\n")
        log.write(f"LLAMA_SERVER_BIN   : {cfg['LLAMA_SERVER_BIN']}\n")
        log.write(f"LOCAL_LIB_DIR      : {cfg['LOCAL_LD_LIBRARY_PATH']}\n")
        log.write("--- LLAMA_SERVER_OUTPUT ---\n")
        log.flush()

        proc = subprocess.Popen(
            cmd,
            stdout=log,
            stderr=subprocess.STDOUT,
            text=True,
            env=env,
            cwd=str(RUN_DIR),
            start_new_session=True,
        )

    pid_path.write_text(str(proc.pid) + "\n", encoding="utf-8")

    url = f"http://{client_host()}:{cfg['PORT']}/v1/models"
    for _ in range(SERVER_READY_TIMEOUT_S):
        if proc.poll() is not None:
            tail = log_path.read_text(encoding="utf-8", errors="ignore").splitlines()[-100:]
            raise RuntimeError(
                "llama-server exited during startup. Last log lines:\n" + "\n".join(tail)
            )

        try:
            response = requests.get(url, timeout=2)
            if response.status_code == 200:
                return proc, log_path, pid_path, cmd, env
        except Exception:
            pass
        time.sleep(1)

    try:
        proc.terminate()
    except Exception:
        pass
    raise RuntimeError(
        f"llama-server did not start within {SERVER_READY_TIMEOUT_S} seconds. Log: {log_path}"
    )


def request_one(prompt, cache_prompt=None, start_barrier=None, slot_id=None):
    url = f"http://{client_host()}:{cfg['PORT']}/completion"
    if cache_prompt is None:
        cache_prompt = bool_cfg(cfg.get("CACHE_PROMPT"), False)

    payload = {
        "prompt": prompt,
        "n_predict": int(cfg["N_GEN"]),
        "temperature": float(cfg["TEMPERATURE"]),
        "top_k": 1,
        "top_p": 1.0,
        "min_p": 0.0,
        "cache_prompt": bool(cache_prompt),
        # Streaming is required for an independent client-side first-token boundary.
        "stream": True,
    }
    if slot_id is not None:
        # llama-server slot IDs are zero-based. The report/console shows them as 1..N.
        payload["id_slot"] = int(slot_id)

    if start_barrier is not None:
        start_barrier.wait()

    t0_wall = time.time()
    t0_mono = time.monotonic()
    first_token_wall = None
    first_token_mono = None
    final_data = {}
    content_parts = []

    with requests.post(
        url,
        json=payload,
        timeout=REQUEST_TIMEOUT_S,
        stream=True,
    ) as response:
        response.raise_for_status()

        # chunk_size=1 avoids requests buffering a large part of the SSE stream,
        # which would make the client first-token timestamp useless.
        for raw_line in response.iter_lines(chunk_size=1, decode_unicode=True):
            if raw_line is None:
                continue
            line = raw_line.strip()
            if not line:
                continue
            if line.startswith("data:"):
                line = line[5:].strip()
            if not line or line == "[DONE]":
                continue

            try:
                event = json.loads(line)
            except json.JSONDecodeError:
                continue

            if isinstance(event, dict):
                # First non-empty streamed output is our independent client boundary.
                content = event.get("content")
                if first_token_mono is None and content not in (None, ""):
                    first_token_wall = time.time()
                    first_token_mono = time.monotonic()

                if isinstance(content, str) and content:
                    content_parts.append(content)

                # The final llama.cpp streaming event carries stop/timings/usage.
                # Merge all metadata so later events can add fields without losing
                # values from earlier ones.
                final_data.update(event)

    t1_wall = time.time()
    t1_mono = time.monotonic()

    # Preserve a content field for compatibility/debugging.
    if content_parts and not final_data.get("content"):
        final_data["content"] = "".join(content_parts)

    return {
        "t0": t0_wall,
        "t1": t1_wall,
        "t0_mono": t0_mono,
        "t1_mono": t1_mono,
        "first_token_t": first_token_wall,
        "first_token_mono": first_token_mono,
        "data": final_data,
    }


def request_many(prompt, count):
    """Submit exactly count requests together and wait for every full response."""
    results = [None] * count
    errors = [None] * count

    # Workers are created first and released together. This minimizes skew between
    # the N requests that are intended to occupy the N configured server slots.
    barrier = threading.Barrier(count + 1)

    def worker(i):
        try:
            # Exact mapping: request i -> llama-server slot i.
            results[i] = request_one(prompt, start_barrier=barrier, slot_id=i)
        except Exception as exc:
            errors[i] = exc

    threads = []
    for i in range(count):
        t = threading.Thread(target=worker, args=(i,), daemon=True)
        t.start()
        threads.append(t)

    barrier.wait()

    for t in threads:
        t.join()

    failed = [(i + 1, err) for i, err in enumerate(errors) if err is not None]
    if failed:
        msg = "; ".join(f"request {i}: {err}" for i, err in failed)
        raise RuntimeError(f"One or more concurrent requests failed: {msg}")

    # Exact group wall time from the first actual HTTP request start
    # to the last full response received.
    group_t0_wall = min(r["t0"] for r in results)
    group_t1_wall = max(r["t1"] for r in results)
    group_t0_mono = min(r["t0_mono"] for r in results)
    group_t1_mono = max(r["t1_mono"] for r in results)

    return {
        "requests": results,
        "group_t0": group_t0_wall,
        "group_t1": group_t1_wall,
        "group_wall_ms": (group_t1_mono - group_t0_mono) * 1000.0,
    }

def row_from_response(ctx, active_slots, request_index, repeat_index, result, monitor, group_wall_ms):
    t0 = result["t0"]
    t1 = result["t1"]
    data = result["data"]
    timings = data.get("timings", {})
    usage = data.get("usage", {})

    # llama-server's own timings: preserved as-is.
    prompt_ms = safe_float(timings.get("prompt_ms")) or 0.0
    decode_ms = safe_float(timings.get("predicted_ms")) or 0.0
    prefill_tps = safe_float(timings.get("prompt_per_second")) or 0.0
    decode_tps = safe_float(timings.get("predicted_per_second")) or 0.0

    prompt_tokens = (
        usage.get("prompt_tokens")
        or data.get("tokens_evaluated")
        or timings.get("prompt_n")
    )
    completion_tokens = (
        usage.get("completion_tokens")
        or data.get("tokens_predicted")
        or timings.get("predicted_n")
    )
    total_tokens = usage.get("total_tokens")
    if total_tokens is None and prompt_tokens is not None and completion_tokens is not None:
        total_tokens = prompt_tokens + completion_tokens

    # Independent client timings. The first streamed token is the practical
    # end-to-end prefill boundary; everything after it until complete response is
    # client-side decode/generation time.
    first_mono = result.get("first_token_mono")
    t0_mono = result["t0_mono"]
    t1_mono = result["t1_mono"]

    client_wall_ms = (t1_mono - t0_mono) * 1000.0
    if first_mono is not None:
        client_prefill_ms = (first_mono - t0_mono) * 1000.0
        client_decode_ms = (t1_mono - first_mono) * 1000.0
        client_first_token_t = result.get("first_token_t")
    else:
        client_prefill_ms = None
        client_decode_ms = None
        client_first_token_t = None

    # Existing GPU/system stage attribution remains based on the server timing
    # fields so historical reports stay comparable.
    pre_t0 = t0
    pre_t1 = t0 + prompt_ms / 1000.0
    dec_t0 = pre_t1
    dec_t1 = t1

    return {
        "file": ctx.name,
        "active_slots": active_slots,
        "request_index": request_index,
        "repeat_index": repeat_index,
        "prompt_target": prompt_size_from_name(ctx),
        "prompt_tokens": prompt_tokens,
        "completion_tokens": completion_tokens,
        "total_tokens": total_tokens,

        # Server-reported metrics (existing fields).
        "prefill_ms": prompt_ms,
        "prefill_tps": prefill_tps,
        "decode_ms": decode_ms,
        "decode_tps": decode_tps,
        "wall_ms": client_wall_ms,

        # Independent client-side measurements (new fields).
        "client_prefill_ms": client_prefill_ms,
        "client_decode_ms": client_decode_ms,
        "client_wall_ms": client_wall_ms,
        "group_wall_ms": group_wall_ms,
        "client_first_token_t": client_first_token_t,

        # Internal exact monotonic boundaries used by aggregate calculations.
        "client_t0_mono": t0_mono,
        "client_first_token_mono": first_mono,
        "client_t1_mono": t1_mono,

        "pre": avg_gpu(monitor.gpu_samples, pre_t0, pre_t1),
        "dec": avg_gpu(monitor.gpu_samples, dec_t0, dec_t1),
        "pre_sys": avg_system(monitor.system_samples, pre_t0, pre_t1),
        "dec_sys": avg_system(monitor.system_samples, dec_t0, dec_t1),
        "t0": t0,
        "t1": t1,
        "pre_t1": pre_t1,
    }


def union_duration_s(intervals):
    """
    Wall-clock duration of the UNION of intervals.

    Overlapping slot intervals are counted once, not summed. This is what makes
    aggregate throughput correct when slots overlap in time or start/end at
    slightly different moments.
    """
    cleaned = []
    for start, end in intervals:
        if start is None or end is None:
            continue
        start = float(start)
        end = float(end)
        if end < start:
            start, end = end, start
        cleaned.append((start, end))

    if not cleaned:
        return None

    cleaned.sort()
    merged_total = 0.0
    cur_start, cur_end = cleaned[0]

    for start, end in cleaned[1:]:
        if start <= cur_end:
            cur_end = max(cur_end, end)
        else:
            merged_total += cur_end - cur_start
            cur_start, cur_end = start, end

    merged_total += cur_end - cur_start
    return merged_total


def aggregate_group_metrics(rows):
    """
    Aggregate throughput for the whole PARALLEL group using REAL client times.

    Prefill:
      sum(prompt tokens across slots)
      / union([request_start, first_output_token]) across slots

    Decode:
      sum(completion tokens across slots)
      / union([first_output_token, full_response_received]) across slots

    Prefill+decode:
      sum(prompt + completion tokens across slots)
      / union([request_start, full_response_received]) across slots

    Because interval unions are used, overlapping work on multiple slots is not
    double-counted in elapsed time, and staggered slot boundaries are respected.
    """
    prompt_tokens_total = sum(
        int(r["prompt_tokens"]) for r in rows if r.get("prompt_tokens") is not None
    )
    completion_tokens_total = sum(
        int(r["completion_tokens"]) for r in rows if r.get("completion_tokens") is not None
    )
    total_tokens = prompt_tokens_total + completion_tokens_total

    prefill_intervals = [
        (r.get("client_t0_mono"), r.get("client_first_token_mono"))
        for r in rows
        if r.get("client_first_token_mono") is not None
    ]
    decode_intervals = [
        (r.get("client_first_token_mono"), r.get("client_t1_mono"))
        for r in rows
        if r.get("client_first_token_mono") is not None
    ]
    total_intervals = [
        (r.get("client_t0_mono"), r.get("client_t1_mono"))
        for r in rows
    ]

    prefill_active_s = union_duration_s(prefill_intervals)
    decode_active_s = union_duration_s(decode_intervals)
    total_active_s = union_duration_s(total_intervals)

    prefill_tps = (
        prompt_tokens_total / prefill_active_s
        if prompt_tokens_total and prefill_active_s and prefill_active_s > 0
        else None
    )
    decode_tps = (
        completion_tokens_total / decode_active_s
        if completion_tokens_total and decode_active_s and decode_active_s > 0
        else None
    )
    total_tps = (
        total_tokens / total_active_s
        if total_tokens and total_active_s and total_active_s > 0
        else None
    )

    return {
        "prompt_tokens_total": prompt_tokens_total,
        "completion_tokens_total": completion_tokens_total,
        "total_tokens": total_tokens,
        "aggregate_prefill_active_s": prefill_active_s,
        "aggregate_decode_active_s": decode_active_s,
        "aggregate_total_active_s": total_active_s,
        "aggregate_prefill_tps": prefill_tps,
        "aggregate_decode_tps": decode_tps,
        "aggregate_total_tps": total_tps,
    }


def classify_stage(ts, batch_results):
    in_pre = False
    in_dec = False
    for result in batch_results:
        t0 = result["t0"]
        t1 = result["t1"]
        data = result["data"]
        prompt_ms = float(data.get("timings", {}).get("prompt_ms", 0))
        pre_end = t0 + prompt_ms / 1000.0
        if t0 <= ts <= pre_end:
            in_pre = True
        if pre_end < ts <= t1:
            in_dec = True
    if in_pre and in_dec:
        return "mixed"
    if in_pre:
        return "prefill"
    if in_dec:
        return "decode"
    return "outside"


def init_system_csv(path):
    with open(path, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow([
            "timestamp_iso",
            "epoch_s",
            "file",
            "active_slots",
            "repeat",
            "stage_hint",
            "cpu_total_pct",
            "cpu_per_core_pct_json",
            "ram_total_mib",
            "ram_used_mib",
            "ram_available_mib",
            "ram_used_pct",
            "swap_total_mib",
            "swap_used_mib",
            "swap_used_pct",
            "gpu_samples_json",
        ])


def append_system_csv(path, ctx, active_slots, repeat_index, samples, batch_results):
    with open(path, "a", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        for s in samples:
            gpu_payload = []
            for g in s.get("gpus", []):
                gpu_payload.append({
                    "index": g["gpu"],
                    "name": g["name"],
                    "pci_bus": g["bus"],
                    "pcie": f"Gen{g['gen']} x{g['width']}",
                    "util_pct": g["util"],
                    "power_w": g["power"],
                    "vram_used_mib": g["mem"],
                })
            writer.writerow([
                datetime.fromtimestamp(s["t"]).astimezone().isoformat(),
                f"{s['t']:.6f}",
                ctx.name,
                active_slots,
                repeat_index,
                classify_stage(s["t"], batch_results),
                s.get("cpu_total_pct"),
                json.dumps(s.get("cpu_cores_pct", []), ensure_ascii=False),
                s.get("ram_total_mib"),
                s.get("ram_used_mib"),
                s.get("ram_available_mib"),
                s.get("ram_used_pct"),
                s.get("swap_total_mib"),
                s.get("swap_used_mib"),
                s.get("swap_used_pct"),
                json.dumps(gpu_payload, ensure_ascii=False),
            ])


def file_text(path):
    try:
        return Path(path).read_text(encoding="utf-8", errors="ignore")
    except Exception:
        return ""


def sysfs_text(path):
    try:
        return Path(path).read_text(encoding="utf-8", errors="ignore").strip()
    except Exception as exc:
        return f"unavailable: {exc}"


def collect_git_info():
    info = {}
    if not (RUN_DIR / ".git").exists():
        return {"git": "unavailable: current directory is not a git repository"}
    info["git_describe"] = run_text(["git", "describe", "--tags", "--always", "--dirty"], cwd=RUN_DIR)
    info["git_commit"] = run_text(["git", "rev-parse", "HEAD"], cwd=RUN_DIR)
    info["git_last_commit"] = run_text(["git", "log", "-1", "--format=%ci%n%s"], cwd=RUN_DIR)
    recent = run_text(["git", "log", "-30", "--format=%H %s"], cwd=RUN_DIR)
    tp_lines = [line for line in recent.splitlines() if "turboprefill" in line.lower()]
    info["git_turboprefill_hint"] = "\n".join(tp_lines[:5]) if tp_lines else "none"
    return info


def make_version_env():
    env = make_server_env()
    # Version query should not need CUDA restriction, but keeping the same env makes
    # the reported binary environment reproducible.
    return env


def collect_model_info():
    model = Path(cfg["MODEL"]).expanduser()
    info = {
        "model_path": str(model),
        "model_filename": model.name,
        "model_size_bytes": model.stat().st_size,
        "model_size_gib": f"{model.stat().st_size / (1024 ** 3):.3f}",
        "gguf_architecture": "unavailable",
        "gguf_tensor_count": "unavailable",
        "gguf_tensor_types": "unavailable",
    }

    # Try the local gguf-py matching the current llama.cpp checkout first.
    local_gguf = RUN_DIR / "gguf-py"
    if local_gguf.is_dir() and str(local_gguf) not in sys.path:
        sys.path.insert(0, str(local_gguf))
    try:
        from gguf.gguf_reader import GGUFReader

        reader = GGUFReader(str(model))
        info["gguf_tensor_count"] = len(reader.tensors)
        counts = Counter(t.tensor_type.name for t in reader.tensors)
        info["gguf_tensor_types"] = ", ".join(f"{k}:{v}" for k, v in sorted(counts.items()))

        field = reader.fields.get("general.architecture")
        if field is not None:
            try:
                value = field.contents()
            except Exception:
                value = field.parts[field.data[0]]
            if hasattr(value, "tolist"):
                value = value.tolist()
            if isinstance(value, bytes):
                value = value.decode(errors="replace")
            if isinstance(value, (list, tuple)) and len(value) == 1:
                value = value[0]
                if isinstance(value, bytes):
                    value = value.decode(errors="replace")
            info["gguf_architecture"] = str(value)
    except Exception as exc:
        info["gguf_reader_error"] = str(exc)

    if bool_cfg(cfg.get("MODEL_HASH"), False):
        h = hashlib.sha256()
        with open(model, "rb") as f:
            for chunk in iter(lambda: f.read(16 * 1024 * 1024), b""):
                h.update(chunk)
        info["model_sha256"] = h.hexdigest()
    else:
        info["model_sha256"] = "disabled (MODEL_HASH=0)"

    return info


def collect_environment():
    server_bin = str(Path(cfg["LLAMA_SERVER_BIN"]).expanduser())
    env = make_version_env()
    info = {
        "TURBOPREFILL": env.get("TURBOPREFILL", "0"),
        "RUN_DIR": str(RUN_DIR),
        "CONFIG_PATH": cfg.get("CONFIG_PATH", ""),
        "LLAMA_SERVER_BIN": server_bin,
        "LOCAL_LD_LIBRARY_PATH": cfg.get("LOCAL_LD_LIBRARY_PATH", ""),
        "CUDA_VISIBLE_DEVICES_effective": EFFECTIVE_CUDA_VISIBLE_DEVICES or "not restricted",
        "selected_gpu_count": str(SELECTED_GPU_COUNT),
        "selected_gpu_models": SELECTED_GPU_MODELS,
        "llama_server_version": run_text([server_bin, "--version"], cwd=RUN_DIR, env=env),
        "uname": run_text(["uname", "-a"]),
        "lscpu": run_text(["lscpu"]),
        "motherboard_vendor": sysfs_text("/sys/class/dmi/id/board_vendor"),
        "motherboard_name": sysfs_text("/sys/class/dmi/id/board_name"),
        "motherboard_version": sysfs_text("/sys/class/dmi/id/board_version"),
        "memory_summary": run_text(["free", "-h"]),
        "memory_modules": run_text(["dmidecode", "--type", "17"], timeout=8),
        "nvidia_smi": run_text([
            "nvidia-smi",
            "--query-gpu=index,name,pci.bus_id,driver_version,memory.total,pcie.link.gen.current,pcie.link.width.current",
            "--format=csv,noheader",
        ]),
        "nvcc": run_text(["nvcc", "--version"]),
        "cmake": run_text(["cmake", "--version"]),
    }
    info.update(collect_git_info())
    info.update(collect_model_info())
    return info


def runtime_log_only(server_log):
    text = file_text(server_log)
    marker = "--- LLAMA_SERVER_OUTPUT ---"
    if marker in text:
        return text.split(marker, 1)[1]
    return text


def detect_turboprefill(server_log, env_info):
    runtime = runtime_log_only(server_log)
    runtime_lines = [line for line in runtime.splitlines() if "turboprefill" in line.lower()]
    git_hint = str(env_info.get("git_turboprefill_hint", "none"))
    requested = str(env_info.get("TURBOPREFILL", "0")).strip()
    active = requested not in {"", "0", "false", "False", "off"}

    version = "not found"
    candidates = runtime_lines + ([] if git_hint == "none" else git_hint.splitlines())
    for line in candidates:
        m = re.search(r"TurboPrefill[^\s,;]*", line, flags=re.IGNORECASE)
        if m:
            version = m.group(0)
            break

    if active:
        status = "active (TURBOPREFILL=1)"
        if not runtime_lines and git_hint == "none":
            status += "; implementation marker not confirmed"
    else:
        if runtime_lines or git_hint != "none":
            status = "TurboPrefill implementation detected; inactive (TURBOPREFILL=0)"
        else:
            status = "original llama.cpp / no TurboPrefill marker detected"

    return {
        "status": status,
        "version": version,
        "runtime_lines": "\n".join(runtime_lines[:20]) if runtime_lines else "none",
    }


def write_raw_csv(raw_csv, results):
    with open(raw_csv, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow([
            "file",
            "active_slots",
            "request_index",
            "repeat",
            "gpu_count",
            "gpu_models",
            "cuda_visible_devices",
            "prompt_tokens",
            "completion_tokens",
            "prefill_ms",
            "prefill_tok_s",
            "decode_ms",
            "decode_tok_s",
            "wall_ms",
            "client_prefill_ms",
            "client_decode_ms",
            "client_wall_ms",
            "group_wall_ms",
            "aggregate_prompt_tokens",
            "aggregate_completion_tokens",
            "aggregate_prefill_active_s",
            "aggregate_decode_active_s",
            "aggregate_total_active_s",
            "aggregate_prefill_tok_s",
            "aggregate_decode_tok_s",
            "aggregate_prefill_decode_tok_s",
        ])
        for row in results:
            writer.writerow([
                row["file"],
                row["active_slots"],
                row["request_index"],
                row["repeat_index"],
                SELECTED_GPU_COUNT,
                SELECTED_GPU_MODELS,
                EFFECTIVE_CUDA_VISIBLE_DEVICES,
                row["prompt_tokens"],
                row["completion_tokens"],
                row["prefill_ms"],
                row["prefill_tps"],
                row["decode_ms"],
                row["decode_tps"],
                row["wall_ms"],
                row["client_prefill_ms"],
                row["client_decode_ms"],
                row["client_wall_ms"],
                row["group_wall_ms"],
                row.get("aggregate_prompt_tokens"),
                row.get("aggregate_completion_tokens"),
                row.get("aggregate_prefill_active_s"),
                row.get("aggregate_decode_active_s"),
                row.get("aggregate_total_active_s"),
                row.get("aggregate_prefill_tps"),
                row.get("aggregate_decode_tps"),
                row.get("aggregate_total_tps"),
            ])


def write_system_stage(f, system):
    if not system:
        f.write("No samples in this stage.\n\n")
        return

    f.write(
        f"CPU total: avg {fmt(system.get('cpu_total_avg'), 1)} %, "
        f"max {fmt(system.get('cpu_total_max'), 1)} %\n\n"
    )
    f.write(
        f"RAM used: avg {fmt(system['ram_used_mib']['avg'], 0)} MiB, "
        f"max {fmt(system['ram_used_mib']['max'], 0)} MiB, "
        f"avg {fmt(system['ram_used_pct']['avg'], 1)} %, "
        f"max {fmt(system['ram_used_pct']['max'], 1)} %\n\n"
    )
    f.write(
        f"Swap used: avg {fmt(system['swap_used_mib']['avg'], 0)} MiB, "
        f"max {fmt(system['swap_used_mib']['max'], 0)} MiB, "
        f"avg {fmt(system['swap_used_pct']['avg'], 1)} %, "
        f"max {fmt(system['swap_used_pct']['max'], 1)} %\n\n"
    )

    f.write("| Logical CPU | avg util % | max util % |\n")
    f.write("|---:|---:|---:|\n")
    for core, values in sorted(system.get("cores", {}).items()):
        f.write(f"| {core} | {fmt(values['avg'], 1)} | {fmt(values['max'], 1)} |\n")
    f.write("\n")


def write_repeat_statistics(f, results):
    if int(cfg.get("REPEATS", "1")) <= 1:
        return

    f.write("\n## Repeat statistics\n\n")
    f.write("| File | Active slots | Requests | Prefill mean | Prefill min | Prefill max | Prefill std | Decode mean | Decode min | Decode max | Decode std |\n")
    f.write("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|\n")

    groups = {}
    for row in results:
        groups.setdefault((row["file"], row["active_slots"]), []).append(row)

    for (file_name, slots), rows in sorted(groups.items()):
        pre = [r["prefill_tps"] for r in rows]
        dec = [r["decode_tps"] for r in rows]
        pre_std = statistics.pstdev(pre) if len(pre) > 1 else 0.0
        dec_std = statistics.pstdev(dec) if len(dec) > 1 else 0.0
        f.write(
            f"| {file_name} | {slots} | {len(rows)} "
            f"| {fmt(statistics.mean(pre))} | {fmt(min(pre))} | {fmt(max(pre))} | {fmt(pre_std)} "
            f"| {fmt(statistics.mean(dec))} | {fmt(min(dec))} | {fmt(max(dec))} | {fmt(dec_std)} |\n"
        )


def write_report(report, results, server_log, server_cmd, env_info, server_pid, errors):
    tp_info = detect_turboprefill(server_log, env_info)

    with open(report, "w", encoding="utf-8") as f:
        f.write("# llama-server fixed-parallel context benchmark report\n\n")

        f.write("## Test header\n\n")
        header_keys = [
            "MODEL", "NGL", "CTX_SIZE", "N_GEN", "BATCH", "UBATCH", "CTK", "CTV",
            "SPEC_TYPE", "SPEC_DRAFT_N_MAX", "SPLIT_MODE", "TENSOR_SPLIT", "PARALLEL",
            "TEMPERATURE", "CACHE_PROMPT", "FLASH_ATTN", "THREADS", "THREADS_BATCH", "REPEATS",
        ]
        for key in header_keys:
            f.write(f"- {key}: `{cfg.get(key, '')}`\n")
        f.write(f"- CUDA_VISIBLE_DEVICES: `{EFFECTIVE_CUDA_VISIBLE_DEVICES}`\n")
        f.write(f"- TURBOPREFILL: `{env_info['TURBOPREFILL']}`\n")
        f.write(f"- TurboPrefill status: `{tp_info['status']}`\n")
        f.write(f"- TurboPrefill version: `{tp_info['version']}`\n")
        f.write(f"- llama.cpp git describe: `{env_info.get('git_describe', 'unavailable')}`\n")
        f.write(f"- llama.cpp git commit: `{env_info.get('git_commit', 'unavailable')}`\n")
        f.write(f"- Server PID: `{server_pid}`\n")
        f.write(f"- KEEP_SERVER_RUNNING: `{cfg.get('KEEP_SERVER_RUNNING', '1')}`\n")
        f.write("- Parallel-slots mode: `PARALLEL=N => exactly N slots and N concurrent requests; request i is pinned to server slot i`\n")
        f.write("- Metrics policy: `server timings preserved + independent client first-token/wall timings + interval-union aggregate throughput`\n")
        f.write(f"- llama_server_log: `{server_log}`\n\n")

        f.write("## Environment\n\n")
        for key, value in env_info.items():
            f.write(f"### {key}\n\n```text\n{value}\n```\n\n")

        f.write("### TurboPrefill runtime markers\n\n```text\n")
        f.write(tp_info["runtime_lines"])
        f.write("\n```\n\n")

        f.write("## Server command\n\n```bash\n")
        f.write(shlex.join(server_cmd))
        f.write("\n```\n\n")
        f.write(f"Server PID: `{server_pid}`  \n")
        f.write(f"Stop command: `kill -INT {server_pid}`\n\n")

        f.write("## Summary\n\n")
        f.write("| File | Active slots | Request | Prompt tokens | Completion tokens | Server prefill tok/s | Server prefill s | Server decode tok/s | Server decode s | Client prefill~ s | Client decode~ s | Client wall s | Group wall s | Group prefill tok/s | Group decode tok/s | Group prefill+decode tok/s |\n")
        f.write("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|\n")
        for row in results:
            f.write(
                f"| {row['file']} "
                f"| {row['active_slots']} "
                f"| {row['request_index']} "
                f"| {row['prompt_tokens']} "
                f"| {row['completion_tokens']} "
                f"| {fmt(row['prefill_tps'])} "
                f"| {fmt(row['prefill_ms'] / 1000.0)} "
                f"| {fmt(row['decode_tps'])} "
                f"| {fmt(row['decode_ms'] / 1000.0)} "
                f"| {fmt(None if row['client_prefill_ms'] is None else row['client_prefill_ms'] / 1000.0)} "
                f"| {fmt(None if row['client_decode_ms'] is None else row['client_decode_ms'] / 1000.0)} "
                f"| {fmt(row['client_wall_ms'] / 1000.0)} "
                f"| {fmt(row['group_wall_ms'] / 1000.0)} "
                f"| {fmt(row.get('aggregate_prefill_tps'))} "
                f"| {fmt(row.get('aggregate_decode_tps'))} "
                f"| {fmt(row.get('aggregate_total_tps'))} |\n"
            )

        f.write("\n## GPU load by stage\n\n")
        for row in results:
            repeat_suffix = f" | repeat={row['repeat_index']}" if int(cfg.get("REPEATS", "1")) > 1 else ""
            f.write(
                f"### {row['file']} | active_slots={row['active_slots']} "
                f"| request={row['request_index']}{repeat_suffix}\n\n"
            )
            for stage_name, samples in [("Prefill", row["pre"]), ("Decode", row["dec"])]:
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

        f.write("\n## CPU / RAM / swap load by stage\n\n")
        for row in results:
            repeat_suffix = f" | repeat={row['repeat_index']}" if int(cfg.get("REPEATS", "1")) > 1 else ""
            f.write(
                f"### {row['file']} | active_slots={row['active_slots']} "
                f"| request={row['request_index']}{repeat_suffix}\n\n"
            )
            f.write("Prefill stage:\n\n")
            write_system_stage(f, row["pre_sys"])
            f.write("Decode stage:\n\n")
            write_system_stage(f, row["dec_sys"])

        write_repeat_statistics(f, results)

        if errors:
            f.write("\n## Errors / partial-run status\n\n")
            for err in errors:
                f.write(f"- {err}\n")


def write_outputs(report, raw_csv, results, server_log, server_cmd, env_info, server_pid, errors):
    write_raw_csv(raw_csv, results)
    write_report(report, results, server_log, server_cmd, env_info, server_pid, errors)


def choose_warmup_context(ctx_files):
    limit = int(cfg.get("WARMUP_MAX_TOKENS", "9000"))
    eligible = [p for p in ctx_files if 0 < prompt_size_from_name(p) <= limit]
    if not eligible:
        return None
    return max(eligible, key=prompt_size_from_name)


def stop_server(proc):
    if proc is None or proc.poll() is not None:
        return
    try:
        proc.send_signal(signal.SIGINT)
        proc.wait(timeout=15)
    except Exception:
        try:
            proc.terminate()
            proc.wait(timeout=5)
        except Exception:
            pass


def main():
    validate_inputs()

    out_dir = Path(cfg["OUTPUT_DIR"]).expanduser() / datetime.now().strftime("%Y%m%d_%H%M%S")
    out_dir.mkdir(parents=True, exist_ok=True)

    report = out_dir / "report.md"
    raw_csv = out_dir / "raw_results.csv"
    system_csv = out_dir / "system_samples.csv"
    init_system_csv(system_csv)

    env_info = collect_environment()
    results = []
    errors = []
    server = None
    server_log = out_dir / "llama_server.log"
    server_cmd = []
    server_pid = "n/a"

    try:
        server, server_log, pid_path, server_cmd, server_env = start_server(out_dir)
        server_pid = server.pid

        ctx_files = sorted(
            Path(cfg["CONTEXTS_DIR"]).expanduser().glob("ctx_*.txt"),
            key=prompt_size_from_name,
        )
        if not ctx_files:
            raise RuntimeError(f"No ctx_*.txt files found in {cfg['CONTEXTS_DIR']}")

        max_parallel = int(cfg["PARALLEL"])
        if max_parallel < 1:
            raise RuntimeError(f"PARALLEL must be >= 1, got {max_parallel}")

        repeats = int(cfg.get("REPEATS", "1"))
        if repeats < 1:
            raise RuntimeError(f"REPEATS must be >= 1, got {repeats}")

        # Custom warmup: one real context, never written to benchmark results.
        # Force cache_prompt=False so the warmup is not intentionally reused.
        if bool_cfg(cfg.get("WARMUP"), True):
            warm_ctx = choose_warmup_context(ctx_files)
            if warm_ctx is None:
                print(
                    f"WARMUP skipped: no ctx_*.txt with target <= "
                    f"{cfg.get('WARMUP_MAX_TOKENS', '9000')} tokens"
                )
            else:
                print(f"WARMUP: {warm_ctx.name} (not recorded)")
                warm_text = warm_ctx.read_text(encoding="utf-8", errors="ignore")
                request_one(warm_text, cache_prompt=False)
                print("WARMUP: done")

        for ctx in ctx_files:
            text = ctx.read_text(encoding="utf-8", errors="ignore")
            active_slots = max_parallel

            for repeat_index in range(1, repeats + 1):
                monitor = Monitor(cfg["MONITOR_INTERVAL"])
                monitor.start()
                batch = None
                try:
                    # Exactly PARALLEL requests are sent together. request_many()
                    # does not return until every request has received its full answer.
                    batch = request_many(text, active_slots)
                finally:
                    monitor.stop()

                batch_results = batch["requests"]

                append_system_csv(
                    system_csv,
                    ctx,
                    active_slots,
                    repeat_index,
                    monitor.system_samples,
                    batch_results,
                )

                rows_this_ctx = []
                for req_i, result in enumerate(batch_results, start=1):
                    row = row_from_response(
                        ctx,
                        active_slots,
                        req_i,
                        repeat_index,
                        result,
                        monitor,
                        batch["group_wall_ms"],
                    )
                    results.append(row)
                    rows_this_ctx.append(row)

                # Only now, after every slot returned its FULL response, calculate
                # the real aggregate rates for this context group.
                group = aggregate_group_metrics(rows_this_ctx)

                for row in rows_this_ctx:
                    row["aggregate_prompt_tokens"] = group["prompt_tokens_total"]
                    row["aggregate_completion_tokens"] = group["completion_tokens_total"]
                    row["aggregate_prefill_active_s"] = group["aggregate_prefill_active_s"]
                    row["aggregate_decode_active_s"] = group["aggregate_decode_active_s"]
                    row["aggregate_total_active_s"] = group["aggregate_total_active_s"]
                    row["aggregate_prefill_tps"] = group["aggregate_prefill_tps"]
                    row["aggregate_decode_tps"] = group["aggregate_decode_tps"]
                    row["aggregate_total_tps"] = group["aggregate_total_tps"]

                repeat_text = f" repeat={repeat_index}" if repeats > 1 else ""
                print(
                    f"{ctx.name} slots={active_slots}{repeat_text}: "
                    f"group_prefill={fmt(group['aggregate_prefill_tps'])} tok/s "
                    f"group_decode={fmt(group['aggregate_decode_tps'])} tok/s "
                    f"group_prefill+decode={fmt(group['aggregate_total_tps'])} tok/s "
                    f"group_wall={batch['group_wall_ms'] / 1000.0:.2f}s"
                )
                print(
                    f"  group_times: "
                    f"prefill_active={fmt(group['aggregate_prefill_active_s'])}s "
                    f"decode_active={fmt(group['aggregate_decode_active_s'])}s "
                    f"total_active={fmt(group['aggregate_total_active_s'])}s "
                    f"tokens={group['prompt_tokens_total']}+{group['completion_tokens_total']}"
                )
                for row in rows_this_ctx:
                    print(
                        f"  slot={row['request_index']}: "
                        f"server_prefill={row['prefill_tps']:.2f} tok/s "
                        f"server_decode={row['decode_tps']:.2f} tok/s "
                        f"client_prefill~={fmt(None if row['client_prefill_ms'] is None else row['client_prefill_ms'] / 1000.0)}s "
                        f"client_decode~={fmt(None if row['client_decode_ms'] is None else row['client_decode_ms'] / 1000.0)}s "
                        f"wall={row['client_wall_ms'] / 1000.0:.2f}s"
                    )

                # Persist successful work only after the entire context group completed.
                write_outputs(
                    report, raw_csv, results, server_log, server_cmd,
                    env_info, server_pid, errors,
                )

    except KeyboardInterrupt:
        errors.append("Benchmark interrupted by user (KeyboardInterrupt). Partial results preserved.")
        print(errors[-1], file=sys.stderr)
    except Exception as exc:
        errors.append(f"{type(exc).__name__}: {exc}")
        print(f"ERROR: {errors[-1]}", file=sys.stderr)
    finally:
        try:
            write_outputs(
                report, raw_csv, results, server_log, server_cmd,
                env_info, server_pid, errors,
            )
        except Exception as report_exc:
            print(f"ERROR while writing partial report: {report_exc}", file=sys.stderr)

        if server is not None:
            if bool_cfg(cfg.get("KEEP_SERVER_RUNNING"), True):
                if server.poll() is None:
                    print(f"llama-server left running: PID={server.pid}, port={cfg['PORT']}")
                    print(f"CUDA_VISIBLE_DEVICES={EFFECTIVE_CUDA_VISIBLE_DEVICES}")
                    print(f"Stop with: kill -INT {server.pid}")
                else:
                    print(f"llama-server is no longer running (exit={server.poll()})")
            else:
                stop_server(server)
                print("llama-server stopped because KEEP_SERVER_RUNNING=0")

    print("REPORT:", report)
    print("CSV:", raw_csv)
    print("SYSTEM CSV:", system_csv)
    print("SERVER LOG:", server_log)

    if errors:
        sys.exit(1)


if __name__ == "__main__":
    main()
