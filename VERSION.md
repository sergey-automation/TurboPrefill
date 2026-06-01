# TurboPrefill v1

First public release candidate.

Validated locally:

- Build: OK
- GPT-OSS 20B server benchmark: OK
- GPT-OSS 120B server benchmark: OK
- Answer quality smoke test: OK
- Runtime disabled path: standard llama.cpp scheduler path
- Runtime enabled path: TurboPrefill for eligible pure prefill batches

Known limitation:

- Built-in `llama-bench pp*` does not activate TurboPrefill because it requests logits for the last prompt token (`n_outputs_all == 1`). Use the provided `llama-server` benchmark scripts for TurboPrefill measurements.