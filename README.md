# TurboPrefill

Multi-GPU prefill acceleration for llama.cpp.

This repository contains a file overlay for llama.cpp and helper scripts for running `llama-server` benchmarks.

## Tested llama.cpp base

```text
2e97c5f96
```

## Install

Clone llama.cpp and check out the tested base:

```bash
git clone https://github.com/ggml-org/llama.cpp.git
cd llama.cpp
git checkout 2e97c5f96
```

Copy TurboPrefill files into the llama.cpp tree:

```bash
/path/to/TurboPrefill/install.sh /path/to/llama.cpp
```

Example:

```bash
/path/to/TurboPrefill/install.sh ~/workspace/projects/llama.cpp
```

Or copy the overlay manually:

```bash
cp -r /path/to/TurboPrefill/files/* /path/to/llama.cpp/
```

## Build

```bash
cd /path/to/llama.cpp
cmake -B build \
  -DGGML_CUDA=ON \
  -DGGML_CUDA_FA=ON \
  -DGGML_CUDA_GRAPHS=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build -j4 --target llama-server
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

## Helper scripts

Benchmark and server helper scripts are in:

```text
benchmarks/gpt20b/
benchmarks/gpt120b/
```

Copy the scripts you need into your llama.cpp checkout, edit the matching `server_config_*.sh`, then run the server or benchmark script.

GPT-OSS 20B example:

```bash
cp -r /path/to/TurboPrefill/benchmarks/gpt20b/* ~/workspace/projects/llama.cpp/
cd ~/workspace/projects/llama.cpp
TURBOPREFILL=1 bash run_server_gpt20b.sh
```

GPT-OSS 120B example:

```bash
mkdir -p ~/workspace/projects/llama.cpp/gpt120b
cp -r /path/to/TurboPrefill/benchmarks/gpt120b/* ~/workspace/projects/llama.cpp/gpt120b/
cd ~/workspace/projects/llama.cpp/gpt120b
TURBOPREFILL=1 bash run_server_gpt120b.sh
```

Open the server UI:

```text
http://127.0.0.1:8081
```

If the config uses `HOST="0.0.0.0"`, other computers on the same local network can open:

```text
http://SERVER_LAN_IP:8081
```

Do not expose `llama-server` directly to the public internet without access control.

## License

MIT. See `LICENSE`.