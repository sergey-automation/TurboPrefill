

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
![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/Llama-3-70B-Dense/RTX3090_4x/parallel_1_output_tokens128/speedup_3090_TurboPrefill_sm_tensor_pipeline_best_ub.png)

Compared to SM Tensor, the amount of data transferred between GPUs is significantly lower with TurboPrefill. This allows TurboPrefill to provide acceleration in cases where the effective performance of SM Tensor is limited by interconnect bandwidth, for example when the GPUs are physically connected through an interface slower than the one supported by the GPUs themselves.

Figure 5. 12 × P104 GPUs connected through PCIe x1 Gen1.

![VLM Response Latency](https://raw.githubusercontent.com/sergey-automation/TurboPrefill-VLM-Validation/main/benchmarks/Llama-3-70B-Dense/P104_12x/P104_TurboPrefill_sm_tensor_pipeline_.png)

The available bandwidth is insufficient for SM Tensor to operate efficiently, but TurboPrefill provides up to 5× speedup over Pipeline Parallel during the prefill phase.

The P104-100 GPU is a mining variant based on the GP104 chip. Among other changes, it was limited to a PCIe 1.0 ×4 interface to discourage its use as a replacement for other GP104-based graphics cards, such as the GTX 1080, , GTX 1070, Quadro P5000, and Tesla P4, which feature a PCIe 3.0 ×16 interface.

A situation similar to that shown in Figure 5 can also occur with modern GPUs featuring high-bandwidth interfaces when they are connected through a bandwidth-limited link. For example, when connecting four RTX 5070 GPUs to a standard PC motherboard using a passive PCIe x16 to 4× PCIe x4 splitter.

Or when building a multi-GPU server where there are not enough PCIe lanes for every GPU to operate at its full interface bandwidth.

Thus, in some scenarios, TurboPrefill not only enables multi-GPU memory scaling, but also delivers higher prefill throughput than Pipeline Parallel and SM Tensor.


**Note**: TurboPrefill is not an alternative to Pipeline Parallel. It operates on top of Pipeline Parallel and is active when using Layer Split with Pipeline Parallel.

**Reproducibility**

**Software used for benchmarking**

* Repository: `sergey-automation/llama.cpp`
* Branch: `turboprefill-vlm-support`
* Commit: `87868f4`

**Raw benchmark data (logs, reports and charts)**

https://github.com/sergey-automation/TurboPrefill-VLM-Validation/tree/main/benchmarks/Llama-3-70B-Dense
