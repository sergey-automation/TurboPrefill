# TurboPrefill

Multi-GPU prefill acceleration for llama.cpp.

This repository contains a file overlay for llama.cpp and helper scripts for running `llama-server` benchmarks.

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
