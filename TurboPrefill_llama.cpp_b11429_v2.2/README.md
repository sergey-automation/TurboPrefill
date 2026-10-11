# TurboPrefill_b11429_v2.2

TurboPrefill port for the exact `llama.cpp` v0.6.0 release.

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
- `tools/server/server-context.cpp`

Copy the directory contents over the root of the exact b11429 source tree while preserving these paths.
