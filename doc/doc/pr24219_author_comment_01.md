
TurboPrefill-VLM-Validation represents a subsequent implementation of the proposed mechanism in which:

- **multi-user operation was enabled;**
- **support for Vision-Language Model (VLM) processing was added.**

Validation of the applicability of **Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill** to Vision Language Models (VLMs).

Application of Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill nearly halved the waiting time before answer generation: from **9.1 s to 4.6 s**.

![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/193452_194641.png)

The model was asked:

>to describe the scene, estimate the number of animals, identify which animal appeared to be the leader, and explain why using five visual clues.

The waiting time before answer generation was derived from the `prompt_eval_ms` values reported by llama.cpp.

Example answer:

> Eight giraffes are walking across a grassy wetland near a river. The animals are light brown with darker patches. The leading giraffe appears to guide the group. Clues: front position, direction of movement, spacing, head orientation, and group alignment.

## Result

| Metric | Baseline | TurboPrefill | Speedup |
|---|---:|---:|---:|
| Waiting time before the response started | 9.1 s | 4.6 s | **1.98× faster** |
| Prefill throughput | 303 tok/s | 604 tok/s | **1.99× higher** |
| Generation throughput | 8.6 tok/s | 8.6 tok/s | **No change (1.00×)** |


## Validation Repository

https://github.com/sergey-automation/TurboPrefill-VLM-Validation
