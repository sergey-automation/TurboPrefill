# ik_llama.cpp_8337e4cd_v6.5

TurboPrefill patch set for the original `ik_llama.cpp`.

- Target commit: `8337e4cd3861406fc04e0854b1409cd1b027fbc9`
- Upstream subject: `Fix Qwen35+ MTP (#2322)`

This patch set is intended only for the commit specified above.

## Files to replace

Replace the following files in the `ik_llama.cpp` source tree:

- `ggml/include/ggml-backend.h`
- `ggml/src/ggml-backend.cpp`
- `src/llama-context.h`
- `src/llama.cpp`
- `examples/server/server-context.cpp`

## Benchmark files

The benchmark contexts and scripts can also be copied to the root directory of the `ik_llama.cpp` repository.

Context directories:

- `contexts_gpt_tokenizer/`
- `contexts_llama3_70b/`

Qwen3.8 benchmark files:

- `bench_Qwen_3.8_ik.py`
- `config_Qwen_3.8_ik.sh`

GPT-OSS-20B benchmark files:

- `bench_gpt20b_ik.py`
- `server_command_20b_ik.sh`

The `.sh` files contain local model paths and must be edited before running the benchmarks.

In particular, update the model paths so that they point to the corresponding GGUF files on your system.

## Running the benchmarks

Before running the benchmarks, edit the corresponding `.sh` configuration files and update the model paths to match the locations of the GGUF files on your system.

### Qwen3.8-27B

Run the baseline without TurboPrefill:

```bash
TURBOPREFILL=0 python3 bench_Qwen_3.8_ik.py
```

Run with TurboPrefill enabled:

```bash
TURBOPREFILL=1 python3 bench_Qwen_3.8_ik.py
```

### GPT-OSS-20B

Run the baseline without TurboPrefill:

```bash
TURBOPREFILL=0 python3 bench_gpt20b_ik.py
```

Run with TurboPrefill enabled:

```bash
TURBOPREFILL=1 python3 bench_gpt20b_ik.py
```

For a valid comparison, use the same model, context files, batch settings, GPU configuration, and other runtime parameters for both `TURBOPREFILL=0` and `TURBOPREFILL=1`.