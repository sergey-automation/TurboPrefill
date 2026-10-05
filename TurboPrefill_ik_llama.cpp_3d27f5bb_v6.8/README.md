# ik_llama.cpp_3d27f5bb_v6.8

- TurboPrefill V6.7 ported to current `ik_llama.cpp` upstream.
- Preserves the V6.7 scheduler replay, MTP compact-output path, short-batch bypass, and first-logits diagnostics.

TurboPrefill patch set for the original `ik_llama.cpp`.

- Target commit: `3d27f5bb6348c4d79edded63b03e9a93efb2f80e`
- Upstream subject: `CUDA implementation for IQ4_KS_R16 (#2586)`
- Port source: `ik_llama.cpp_8337e4cd_v6.7`

This patch set is intended only for the commit specified above.

## Files to replace

Replace the following files in the `ik_llama.cpp` source tree:

- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `src/llama-context.h`
- `src/llama.cpp`
- `examples/server/server-context.cpp`

`ggml/src/ggml-cuda.cu` is intentionally not included: the file distributed with V6.7 is byte-identical to its `8337e4cd` upstream version and contains no TurboPrefill changes.
