# ik_llama.cpp_8337e4cd_v6.6.3
- Moved several TurboPrefill checks out of the decode hot path to reduce decode overhead.

TurboPrefill patch set for the original `ik_llama.cpp`.

- Target commit: `8337e4cd3861406fc04e0854b1409cd1b027fbc9`
- Upstream subject: `Fix Qwen35+ MTP (#2322)`

This patch set is intended only for the commit specified above.

## Files to replace

Replace the following files in the `ik_llama.cpp` source tree:

- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `ggml/src/ggml-cuda.cu`
- `src/llama-context.h`
- `src/llama.cpp`
- `examples/server/server-context.cpp`
