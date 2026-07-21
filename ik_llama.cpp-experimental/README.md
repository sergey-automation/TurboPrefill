# Experimental TurboPrefill port for ik_llama.cpp

This directory contains an experimental port of TurboPrefill by Trykhlieb to `ik_llama.cpp`.

Based on:

- Project: `ik_llama.cpp`
- Author: Ivan Kawrakow (`ikawrakow`)
- Base commit: `6198a356`

## Status

This is an experimental implementation for the specific `ik_llama.cpp` commit listed above.

Compatibility with other commits is not guaranteed.

## Directory structure

- `port/` — modified source files for the TurboPrefill port
- `benchmarks/` — benchmark scripts, test contexts, and benchmark results

The `port/` directory contains:

- clean files for normal use
- diagnostic files with extended logging for validation and future ports

## Installation

Clone the required version of `ik_llama.cpp`:

```bash
git clone https://github.com/ikawrakow/ik_llama.cpp.git
cd ik_llama.cpp
git checkout 6198a356
```

Copy the modified files from the port/ directory and replace the files with the same names in the ik_llama.cpp source tree.

Then build ik_llama.cpp normally.

## Running benchmarks

The benchmark files are located in:
benchmarks/

## Baseline:
```bash
TURBOPREFILL=0 python3 bench_gpt20b_ik.py
```

## TurboPrefill:

```bash
TURBOPREFILL=1 python3 bench_gpt20b_ik.py
```

Benchmark results for both modes are included in the benchmarks directory.

## Development

The initial port, code adaptation, diagnostic logging, cleanup, and preparation of reusable diagnostic files were performed with the assistance of Codex and GPT-5.6 during OpenAI Build Week.

TurboPrefill was developed by Trykhlieb.











