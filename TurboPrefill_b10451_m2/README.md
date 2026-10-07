# TurboPrefill_b10451_m2

For Qwen3.8-27B in MTP mode, multi-slot operation is implemented.

## Exact target

- llama.cpp build: `b10451`
- commit: `10bf611e533d81f739128304991c5e133c6aebd8`

Do not apply this replacement set to another llama.cpp commit without a new port and build check.

## Replacement files

- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `src/llama-batch.cpp`
- `src/llama-batch.h`
- `src/llama-context.cpp`
- `src/llama-context.h`
- `tools/server/server-context.cpp`

Copy the directory contents over the root of the exact b10451 source tree while preserving these paths.


