# TurboPrefill V8 for ik_llama.cpp 5005

Self-contained replacement set for the clean `ik_llama.cpp` 5005 source tree.

- Target commit: `3d27f5bb6348c4d79edded63b03e9a93efb2f80e`
- Upstream subject: `CUDA implementation for IQ4_KS_R16 (#2586)`

This set targets only the commit above. Do not apply it to another upstream revision.

## Files to replace

Copy the files from this folder into the clean source tree, preserving paths and replacing existing files:

- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `src/llama-context.h`
- `src/llama.cpp`
- `examples/server/server-context.cpp`


## TurboPrefill

Enable TurboPrefill with `TURBOPREFILL=1`.

V8 adds a signature check for the TurboPrefill UB prefix. A UB is replayed only while its actual signature matches the first full UB: token count, sequence layout, sequence counts, output count and equality of tokens per sequence. The first partial or differently shaped UB ends the TurboPrefill prefix.
