# TurboPrefill V6.9.1_multigpu_load for ik_llama.cpp 5005

Self-contained replacement set for the clean `ik_llama.cpp` 5005 source tree.

- Target commit: `3d27f5bb6348c4d79edded63b03e9a93efb2f80e`
- Upstream subject: `CUDA implementation for IQ4_KS_R16 (#2586)`

This set targets only the commit above. Do not apply it to another upstream revision.

## Files to replace

Copy the files from this folder into the clean source tree, preserving paths and replacing existing files:

- `common/common.cpp`
- `common/common.h`
- `examples/server/server-context.cpp`
- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `include/llama.h`
- `spm-headers/llama.h`
- `src/llama-context.h`
- `src/llama-model-loader.cpp`
- `src/llama-model-loader.h`
- `src/llama.cpp`

## Parallel loading

Normal weight loading is sequential: weights are copied to the first GPU, then to the second GPU, and so on. While one GPU is loading, the other GPUs are idle.

With `--parallel-load`, a separate loading worker is created for each GPU. As soon as a GPU's CUDA buffer is ready, its weights begin loading without waiting for the buffers of the remaining GPUs. Multiple GPUs can receive weights at the same time.

This is useful when the storage device or system RAM can supply data faster than a single GPU can receive it over PCIe.

Example: an M.2 NVMe drive connected through PCIe Gen3 x4 and 12 GPUs, each connected through PCIe Gen1 x1. A fast M.2 NVMe drive can provide about 2–3 GiB/s of read throughput, while one GPU on PCIe Gen1 x1 can receive about 0.25 GiB/s. Sequential loading is limited by the connection speed of one GPU. With parallel loading, multiple GPUs receive data simultaneously, so the aggregate loading speed can approach the M.2 NVMe throughput. This reduces the time spent waiting for multi-GPU model loading.

If GPUs are connected with full PCIe links, for example PCIe x16 or x8, there may be little or no benefit: one GPU can already receive data at least as fast as the storage device, so the limiting factor is the storage device or system RAM.

`--parallel-load` affects only model loading at server startup. It does not change the inference algorithm, TurboPrefill, or MTP multithreading.

## Instructions for AI

```bash
BIN="$HOME/TurboPrefill_ik_llama.cpp_5005_V6.9.1/build/bin"
```

### Ordinary model launch

```bash
env -u LD_PRELOAD LD_LIBRARY_PATH="$BIN" "$BIN/llama-server" -m /path/to/model.gguf --host 0.0.0.0 --port 8088 -ngl 999 -c 33000 -b 4096 -ub 32 -np 1 -ctk f16 -sm layer --spec-type mtp:n_max=3
```

### The same model with TurboPrefill

```bash
env -u LD_PRELOAD TURBOPREFILL=1 LD_LIBRARY_PATH="$BIN" "$BIN/llama-server" -m /path/to/model.gguf --host 0.0.0.0 --port 8088 -ngl 999 -c 33000 -b 4096 -ub 32 -np 1 -ctk f16 -sm layer --spec-type mtp:n_max=3
```

### The same model with parallel loading

```bash
env -u LD_PRELOAD LD_LIBRARY_PATH="$BIN" "$BIN/llama-server" --parallel-load -m /path/to/model.gguf --host 0.0.0.0 --port 8088 -ngl 999 -c 33000 -b 4096 -ub 32 -np 1 -ctk f16 -sm layer --spec-type mtp:n_max=3
```

### The same model with TurboPrefill and parallel loading

```bash
env -u LD_PRELOAD TURBOPREFILL=1 LD_LIBRARY_PATH="$BIN" "$BIN/llama-server" --parallel-load -m /path/to/model.gguf --host 0.0.0.0 --port 8088 -ngl 999 -c 33000 -b 4096 -ub 32 -np 1 -ctk f16 -sm layer --spec-type mtp:n_max=3
```
