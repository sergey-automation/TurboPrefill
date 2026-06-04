# [RFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill


## 1. Status: Proof of Concept (PoC)

This RFC describes an experimental scheduling mechanism implemented in the TurboPrefill project and intended for discussion of the architectural approach.

## 2. The Problem

With `split_mode = layer`, processing of a single request during the `prefill` phase is performed by passing each `ubatch` sequentially through the GPU pipeline.

When processing a single `ubatch`, GPU stages are utilized sequentially: early GPUs become idle after completing their work, while later GPUs remain idle waiting for input data.

This limits GPU utilization efficiency and reduces performance scaling as the number of devices increases.

## 3. Proposed Approach

Within the scope of this RFC, the term **Intra-Prompt Pipeline Scheduling** refers to the request-internal scheduling mechanism for the `prefill` phase described below.

The proposed approach does not modify the division of a request into `ubatch` units.

During the `prefill` phase, `ubatch` instances are pre-classified. `ubatch` instances requiring the standard execution order continue to be processed by the existing scheduling mechanism. `ubatch` instances suitable for pipeline execution are routed to the Intra-Prompt Pipeline Scheduling mode implemented in TurboPrefill.

In this mode, `ubatch` instances are accumulated until the final `ubatch` of the current batch is received, after which they are executed sequentially through the layer-split GPU pipeline.

The next `ubatch` begins processing immediately after the previous `ubatch` completes execution on the corresponding GPU stage. It is therefore not necessary to wait for the previous `ubatch` to pass through all GPUs before starting execution of the next one.

As a result, the number of GPUs simultaneously performing useful work increases.

## 4. Scope

Intra-Prompt Pipeline Scheduling is intended to accelerate the `prefill` phase when processing large single requests on multi-GPU configurations.

The approach is designed for **Single-User Mode**, where compute resources are dedicated to a single active request.

## 5. Limitations

Intra-Prompt Pipeline Scheduling is a request-internal scheduling mechanism. It does not introduce parallelism between independent requests and does not replace existing multi-user batching mechanisms.

The approach is intended to accelerate the `prefill` phase and does not affect `decode` performance.

Intra-Prompt Pipeline Scheduling is applied only to `ubatch` instances that do not contain logits output requests.

For this reason, the standard `llama-bench` tool is not suitable for evaluating this mode, since its prefill tests contain logits output requests and therefore continue to be processed by the standard scheduling path.

## 6. PoC Results

Results for a context length of 16,373 tokens. Full results for all tested context lengths are provided below and are available in the repository.

```text
Platform                      GPU   Baseline   TurboPrefill   Gain
------------------------------------------------------------------
10x P104-100                  10       77          181        +135%
4x RTX 3090                    4     1477         2758         +87%
5x RTX 5060 Ti                 5     1993         3886         +95%
8x RTX 5060 Ti                 8     1963         4380        +123%
```

## 7. Computational Correctness

Intra-Prompt Pipeline Scheduling does not modify the mathematical computation model.

The execution order of individual layers and the order of data propagation through each layer remain unchanged.

Only the execution scheduling order between GPU stages is modified.

## 8. Discussion Topics

* Possible integration into `ggml-backend-sched`.
* Applicability to other split modes.
* Applicability to systems with P2P/NVLink support.

This RFC is published for discussion of the architectural approach and for collecting feedback on possible future directions of development.
## 9. Implementation Status

The current implementation is provided as an isolated overlay module and does not require modifications to the model architecture.

The mode can be enabled through the `TURBOPREFILL=1` environment variable.

Source code, installation scripts, benchmark data, and measurement results are available in the separate TurboPrefill repository.

## 10. Full Benchmark Results

The complete benchmark tables and graphs are provided below.
