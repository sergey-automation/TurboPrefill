# TurboPrefill

Multi-GPU prefill acceleration for llama.cpp.

This repository contains a file overlay for llama.cpp and helper scripts for running `llama-server` benchmarks.

## Performance Benchmark (GPT-OSS-120B)

![TurboPrefill Benchmark](benchmarks/RTX5060ti_8x/Turboprefill_8xRTX5060ti.png)

### Summary Results
| Prompt Tokens | Baseline (8x GPU) tok/s | TurboPrefill tok/s | Speedup Gain |
| :--- | :---: | :---: | :---: |
| 255 | 1038| 1043 | **1.00x** |
| 504 | 1609 | 1613 | **1.00x** |
| 1017 | 1762 | 1765 | **1.00x** |
| 2044 | 2021 | 2022 | **1.00x** |
| 4076 | 2046 | 3180 | **1.55x** |
| 6142 | 2122 | 3668 | **1.73x** |
| 8164 | 2076 | 4111 | **1.98x** |
| 12280 | 2035 | 4421 | **2.17x** |
| 16373 | 1963 | 4380 | **2.23x** |
| 24560 | 1853 | 3684 | **1.99x** |
| 32761 | 1776 | 3359 | **1.89x** |

# How TurboPrefill Was Created

For more than 20 years, I worked on the design, construction, and optimization of custom industrial production lines and control systems.

While experimenting with running local AI models using llama.cpp on multi-GPU systems in layer-split mode, I noticed a well-known characteristic of long-context prefill execution.

In layer-split mode, the model is distributed across multiple GPUs by layers. Under the standard execution path, each ubatch passes sequentially through all model layers. As a result, some GPUs remain idle while waiting for the previous ubatch to complete processing through the remaining layers.

While analyzing the scheduler's behavior, I began asking a simple question: does prefill really require waiting for the previous ubatch to traverse the entire model before the next ubatch can begin?

For decode, such a dependency does exist. However, during prefill, the next ubatch can start processing on a layer immediately after the previous ubatch has finished on that layer, without waiting for it to complete the entire model.

To test this idea, I created an experimental execution path that later became TurboPrefill.

The core idea is not to modify the model, mathematical computations, or attention algorithms. TurboPrefill changes only the scheduling strategy used to process a series of ubatches inside the scheduler.

If GPUs are viewed as stations on a production line, the standard approach sends one workpiece through every station before starting the next one. As a result, parts of the equipment periodically sit idle while waiting for previous stages to finish.

TurboPrefill is intended to keep multiple ubatches active within the pipeline simultaneously. This allows each GPU to begin processing the next ubatch as soon as its own work is complete, without waiting for the previous ubatch to finish across the entire GPU chain.

In simplified form:

Standard scheduler:

```text
step    1234567890123
GPU(1)  #000#000#0000
GPU(2)  0#000#000#000
GPU(3)  00#000#000#00
GPU(4)  000#000#000#0
```

TurboPrefill:

```text
step    1234567
GPU(1)  ###0000
GPU(2)  0###000
GPU(3)  00###00
GPU(4)  000###0
```

TurboPrefill does not modify model weights, computations, or inference results. Only the execution order of prefill workloads inside the scheduler is changed.

As a result, idle time between processing stages can be reduced and higher prefill performance can be achieved on long contexts while preserving identical model outputs.

TurboPrefill is not intended to be a universal accelerator for all llama.cpp workloads.

It is specifically designed for long single-request prefill workloads running in multi-GPU layer-split mode, where underutilization of available hardware is most visible.

The idea behind TurboPrefill did not come from modifying the mathematical side of the model. It came from viewing multi-GPU inference as a production pipeline, where the primary focus is hardware utilization, reducing idle time, and improving overall system throughput.

## Tested llama.cpp base

```text
2e97c5f96
```

## Install


Clone TurboPrefill:

```bash
cd /workspace
git clone https://github.com/sergey-automation/TurboPrefill.git
chmod +x /workspace/TurboPrefill/install.sh
```

Clone llama.cpp and check out the tested base:

```bash
mkdir -p /workspace/projects
cd /workspace/projects

git clone https://github.com/ggml-org/llama.cpp.git
cd llama.cpp
git checkout 2e97c5f96
git rev-parse HEAD
```

Copy TurboPrefill files into the llama.cpp tree:
The benchmark scripts are not installed automatically.
Copy the benchmark files you want to use into the llama.cpp root directory.
```bash
chmod +x /workspace/TurboPrefill/install.sh
/workspace/TurboPrefill/install.sh /workspace/projects/llama.cpp
```
Benchmark scripts (GPT-OSS-20B):
```bash
cp -r /workspace/TurboPrefill/benchmarks/gpt20b/* \
/workspace/projects/llama.cpp/
```
Benchmark scripts (GPT-OSS-120B):

```bash
cp -r /workspace/TurboPrefill/benchmarks/gpt120b/* \
/workspace/projects/llama.cpp/
```

## Build

```bash
cd /workspace/projects/llama.cpp

cmake -B build \
  -DGGML_CUDA=ON \
  -DGGML_CUDA_FA=ON \
  -DGGML_CUDA_GRAPHS=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build -j4 --target llama-server
```
## Python dependency
Benchmark scripts require requests:
```bash
pip install requests
```

## Download models
Create model directory:
```bash
mkdir -p /workspace/models
cd /workspace/models
```
GPT-OSS 20B:
```bash
hf download unsloth/gpt-oss-20b-GGUF \
  gpt-oss-20b-Q4_K_M.gguf \
  --local-dir /workspace/models
```
GPT-OSS 120B:
```bash
hf download unsloth/gpt-oss-120b-GGUF \
  Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf \
  Q4_K_M/gpt-oss-120b-Q4_K_M-00002-of-00002.gguf \
  --local-dir /workspace/models
```
Check files:
```bash
ls -lh /workspace/models
ls -lh /workspace/models/Q4_K_M
```
## Note
 llama-bench pp tests currently do not exercise TurboPrefill because they use a benchmark batch mode with n_outputs_all=1. TurboPrefill is enabled for real prompt prefill paths where n_outputs_all=0, such as llama-server long prompt processing.
## Benchmark scripts
Benchmark scripts are designed to be copied into the llama.cpp checkout and executed from there.

Benchmark files must be copied into the llama.cpp root directory.
Benchmark scripts must be executed from the llama.cpp root directory.
Copy GPT-OSS 20B scripts:
```bash
cp -r /workspace/TurboPrefill/benchmarks/gpt20b/* /workspace/projects/llama.cpp/
```
Copy GPT-OSS 120B scripts:
```bash
cp -r /workspace/TurboPrefill/benchmarks/gpt120b/* /workspace/projects/llama.cpp/
```
## Run benchmarks
GPT-OSS 20B baseline:
```bash
cd /workspace/projects/llama.cpp
TURBOPREFILL=0 python3 bench_server_gpt20b.py
```
GPT-OSS 20B with TurboPrefill:
```bash
cd /workspace/projects/llama.cpp
TURBOPREFILL=1 python3 bench_server_gpt20b.py
```
GPT-OSS 120B baseline:
```bash
cd /workspace/projects/llama.cpp
TURBOPREFILL=0 python3 bench_server_gpt120b.py
```
GPT-OSS 120B with TurboPrefill:
```bash
cd /workspace/projects/llama.cpp
TURBOPREFILL=1 python3 bench_server_gpt120b.py
```
Reports are saved to the OUTPUT_DIR configured in:
- server_config_20b.sh
- server_config_gpt120b.sh
If you see:
```text
$'\r': command not found
```
convert shell scripts to Unix format:
```bash
sed -i 's/\r$//' *.sh
```
## Run server UI
GPT-OSS 20B:
```bash
cd /workspace/projects/llama.cpp
TURBOPREFILL=1 bash run_server_gpt20b.sh
```
GPT-OSS 120B:
```bash
cd /workspace/projects/llama.cpp
TURBOPREFILL=1 bash run_server_gpt120b.sh
```
On VAST, use SSH tunnel from your local Windows CMD:
```bash
ssh -L 8081:127.0.0.1:8081 -p YOUR_SSH_PORT root@YOUR_SSH_HOST
```
Example:
```bash
ssh -L 8081:127.0.0.1:8081 -p 26865 root@ssh4.vast.ai
```
Open in browser:
```bash
http://127.0.0.1:8081
```
Do not expose llama-server directly to the public internet without access control.

## Notes for Windows / WinSCP users
If you edit .sh files from Windows, save them with Unix line endings: LF, not CRLF.

If you see this error:
$'\r': command not found

fix the files:
```bash
cd /workspace/projects/llama.cpp

sed -i 's/\r$//' *.sh
```

## Enable or disable TurboPrefill

TurboPrefill is controlled at runtime.

Enable:

```bash
TURBOPREFILL=1 ./build/bin/llama-server ...
```

Disable:

```bash
unset TURBOPREFILL
./build/bin/llama-server ...
```

Disabled values are: unset, `0`, `false`, `off`.

## Tested VAST configuration
VAST Template: NVIDIA CUDA 
Container disk: 200 GB 
OS: Ubuntu 24.04.4 LTS 
GPU: 8x RTX 5060 Ti 16GB
Driver: 580.159.03 CUDA: 13.0
nvcc: 13.0.88 gcc: 13.3.0 
cmake: 3.28.3
git: 2.43.0 
P2P: not supported
NVLink: not present

## License

MIT. See `LICENSE`.
