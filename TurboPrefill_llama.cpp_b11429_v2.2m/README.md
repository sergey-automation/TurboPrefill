# TurboPrefill_llama.cpp_b11429_v2.2m

TurboPrefill port for the exact `llama.cpp` v0.6.0 release, extended with parallel GPU weight loading.

## Exact target

- llama.cpp build: `b11429`
- release tag: `v0.6.0`
- commit: `d81235049384534c167caea52b85a694f6103d14`

Do not apply this replacement set to another llama.cpp commit without a new port and build check.

## Replacement files

- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `src/llama-batch.cpp`
- `src/llama-batch.h`
- `src/llama-context.cpp`
- `src/llama-context.h`
- `src/llama-model.cpp`
- `src/llama-model-loader.cpp`
- `src/llama-model-loader.h`
- `include/llama.h`
- `common/arg.cpp`
- `common/common.cpp`
- `common/common.h`
- `tools/server/server-context.cpp`

Copy the directory contents over the root of the exact b11429 source tree while preserving these paths.

## Parallel GPU weight loading

Pass `--parallel-load` together with `--split-mode layer`. Each GPU layer-split context uploads its weights in a separate worker while buffers for the remaining contexts are being prepared. The mode requires the normal mmap loader; it remains inactive for non-mmap loading.

### Parallel loading without TurboPrefill

```bash
./llama-server \
  -m model.gguf \
  --split-mode layer \
  --tensor-split 1,1,1 \
  --parallel-load
```

### Parallel loading with TurboPrefill

```bash
TURBOPREFILL=1 ./llama-server \
  -m model.gguf \
  --split-mode layer \
  --tensor-split 1,1,1 \
  --parallel-load
```

When workers actually start, the log contains:

```text
TurboPrefill_llama.cpp_b11429_v2.2m: parallel GPU weight loading active: N layer-split worker(s)
```
