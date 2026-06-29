

Comparison of TurboPrefill (Pipeline Parallel + Intra-Prompt Pipeline Scheduling) with Pipeline Parallel and SM Tensor

**Test configuration**

* **Model:** Meta-Llama-3-70B-Instruct-Q4_K_M.gguf
* **Maximum context length:** 107k tokens
* **Tensor split: 18/21/21/21**
* **Parallel slots:** 1
* **Benchmark script:** `bench_server_Llama-3-70B_parallel_slots.py`


Figure 1. Comparison with the optimal ubatch for Pipeline Parallel and SM Tensor, but not the optimal ubatch for TurboPrefill.

![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/Llama-3-70B-Dense/RTX3090_4x/parallel_1_output_tokens128/Ub1024/ub1024_TurboPrefill_sm_tensor_pipeline.png)


Figure 2. Comparison with an optimal ubatch for TurboPrefill, but not the optimal ubatch for Pipeline Parallel and SM Tensor.

![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/Llama-3-70B-Dense/RTX3090_4x/parallel_1_output_tokens128/Ub128/ub128_TurboPrefill_sm_tensor_pipeline.png)


Figure 3. Comparison with the optimal ubatches for Pipeline Parallel, SM Tensor, and TurboPrefill.
![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/Llama-3-70B-Dense/RTX3090_4x/parallel_1_output_tokens128/TurboPrefill_sm_tensor_pipeline_best_ub.png)

Figure 4. TurboPrefill speedup relative to Pipeline Parallel and SM Tensor.
![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/Llama-3-70B-Dense/RTX3090_4x/parallel_1_output_tokens128/speedup_TurboPrefill_sm_tensor_pipeline_best_ub.png)


**Reproducibility**

**Software used for benchmarking**

* Repository: `sergey-automation/llama.cpp`
* Branch: `turboprefill-vlm-support`
* Commit: `87868f4`

**Raw benchmark data (logs, reports and charts)**

https://github.com/sergey-automation/TurboPrefill-VLM-Validation/tree/main/benchmarks/Llama-3-70B-Dense
