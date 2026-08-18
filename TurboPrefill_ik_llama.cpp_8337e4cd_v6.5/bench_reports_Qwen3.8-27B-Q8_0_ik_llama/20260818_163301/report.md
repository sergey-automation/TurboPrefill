# llama-server parallel-slots context benchmark report

## Test header

- MODEL: `/mnt/models/AI/LLM/Qwen3.8-27B-Q8_0.gguf`
- NGL: `999`
- CTX_SIZE: `260000`
- N_GEN: `128`
- BATCH: `4097`
- UBATCH: `32`
- CTK: `f16`
- CTV: `f16`
- SPEC_TYPE: `mtp`
- SPEC_DRAFT_N_MAX: `3`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `9/11/11/11/11/11/9`
- PARALLEL: `1`
- TEMPERATURE: `0.15`
- CACHE_PROMPT: `0`
- FLASH_ATTN: `auto`
- THREADS: `auto`
- THREADS_BATCH: `auto`
- REPEATS: `1`
- CUDA_VISIBLE_DEVICES: `0,1,2,3,4,5,6`
- TURBOPREFILL: `0`
- TurboPrefill status: `TurboPrefill implementation detected; inactive (TURBOPREFILL=0)`
- TurboPrefill version: `TurboPrefill`
- llama.cpp git describe: `t0002-1026-g8337e4cd-dirty`
- llama.cpp git commit: `8337e4cd3861406fc04e0854b1409cd1b027fbc9`
- Server PID: `5162`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `active_slots=1..PARALLEL`
- Metrics policy: `server per-request timings only; no combined throughput calculated`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/bench_reports_Qwen3.8-27B-Q8_0_ik_1708/20260818_163301/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
```

### RUN_DIR

```text
/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd
```

### CONFIG_PATH

```text
/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/config_Qwen_3.8_ik.sh
```

### LLAMA_SERVER_BIN

```text
/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/build/bin/llama-server
```

### LOCAL_LD_LIBRARY_PATH

```text
/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/build/bin
```

### CUDA_VISIBLE_DEVICES_effective

```text
0,1,2,3,4,5,6
```

### selected_gpu_count

```text
7
```

### selected_gpu_models

```text
NVIDIA P104-100 x7
```

### llama_server_version

```text
version: 4840 (8337e4cd)
built with cc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0 for x86_64-linux-gnu
```

### uname

```text
Linux turboprefill 6.17.0-29-generic #29~24.04.1-Ubuntu SMP PREEMPT_DYNAMIC Mon May 11 10:30:58 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
```

### lscpu

```text
Архитектура:                             x86_64
CPU op-mode(s):                          32-bit, 64-bit
Address sizes:                           39 bits physical, 48 bits virtual
Порядок байт:                            Little Endian
CPU(s):                                  4
On-line CPU(s) list:                     0-3
ID прроизводителя:                       GenuineIntel
Имя модели:                              Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
Семейство ЦПУ:                           6
Модель:                                  158
Потоков на ядро:                         1
Ядер на сокет:                           4
Сокетов:                                 1
Степпинг:                                9
CPU(s) scaling MHz:                      26%
CPU max MHz:                             3800.0000
CPU min MHz:                             800.0000
BogoMIPS:                                6799.81
Флаги:                                   fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault pti ssbd ibrs ibpb stibp fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp md_clear flush_l1d arch_capabilities
L1d cache:                               128 KiB (4 instances)
L1i cache:                               128 KiB (4 instances)
L2 cache:                                1 MiB (4 instances)
L3 cache:                                6 MiB (1 instance)
NUMA node(s):                            1
NUMA node0 CPU(s):                       0-3
Vulnerability Gather data sampling:      Vulnerable
Vulnerability Ghostwrite:                Not affected
Vulnerability Indirect target selection: Not affected
Vulnerability Itlb multihit:             KVM: Mitigation: VMX unsupported
Vulnerability L1tf:                      Mitigation; PTE Inversion
Vulnerability Mds:                       Mitigation; Clear CPU buffers; SMT disabled
Vulnerability Meltdown:                  Mitigation; PTI
Vulnerability Mmio stale data:           Mitigation; Clear CPU buffers; SMT disabled
Vulnerability Old microcode:             Not affected
Vulnerability Reg file data sampling:    Not affected
Vulnerability Retbleed:                  Mitigation; IBRS
Vulnerability Spec rstack overflow:      Not affected
Vulnerability Spec store bypass:         Mitigation; Speculative Store Bypass disabled via prctl
Vulnerability Spectre v1:                Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:                Mitigation; IBRS; IBPB conditional; STIBP disabled; RSB filling; PBRSB-eIBRS Not affected; BHI Not affected
Vulnerability Srbds:                     Mitigation; Microcode
Vulnerability Tsa:                       Not affected
Vulnerability Tsx async abort:           Mitigation; TSX disabled
Vulnerability Vmscape:                   Mitigation; IBPB before exit to userspace
```

### motherboard_vendor

```text
ASUSTeK COMPUTER INC.
```

### motherboard_name

```text
B250 MINING EXPERT
```

### motherboard_version

```text
Rev X.0x
```

### memory_summary

```text
всего        занят        своб      общая  буф/врем.   доступно
Память:         15Gi       2.1Gi        12Gi       177Mi       1.4Gi        13Gi
Подкачка:       23Gi          0B        23Gi
```

### memory_modules

```text
unavailable: Command '['dmidecode', '--type', '17']' returned non-zero exit status 1.
```

### nvidia_smi

```text
0, NVIDIA P104-100, 00000000:01:00.0, 535.309.01, 8192 MiB, 1, 1
1, NVIDIA P104-100, 00000000:02:00.0, 535.309.01, 8192 MiB, 1, 1
2, NVIDIA P104-100, 00000000:0A:00.0, 535.309.01, 8192 MiB, 1, 1
3, NVIDIA P104-100, 00000000:0C:00.0, 535.309.01, 8192 MiB, 1, 1
4, NVIDIA P104-100, 00000000:0D:00.0, 535.309.01, 8192 MiB, 1, 1
5, NVIDIA P104-100, 00000000:0E:00.0, 535.309.01, 8192 MiB, 1, 1
6, NVIDIA P104-100, 00000000:0F:00.0, 535.309.01, 8192 MiB, 1, 1
7, NVIDIA P104-100, 00000000:10:00.0, 535.309.01, 8192 MiB, 1, 1
8, NVIDIA P104-100, 00000000:11:00.0, 535.309.01, 8192 MiB, 1, 1
9, NVIDIA P104-100, 00000000:12:00.0, 535.309.01, 8192 MiB, 1, 1
10, NVIDIA P104-100, 00000000:13:00.0, 535.309.01, 8192 MiB, 1, 1
11, NVIDIA P104-100, 00000000:14:00.0, 535.309.01, 8192 MiB, 1, 1
```

### nvcc

```text
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2023 NVIDIA Corporation
Built on Fri_Jan__6_16:45:21_PST_2023
Cuda compilation tools, release 12.0, V12.0.140
Build cuda_12.0.r12.0/compiler.32267302_0
```

### cmake

```text
cmake version 3.28.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

### git_describe

```text
t0002-1026-g8337e4cd-dirty
```

### git_commit

```text
8337e4cd3861406fc04e0854b1409cd1b027fbc9
```

### git_last_commit

```text
2026-08-15 19:35:03 +0200
Fix Qwen35+ MTP (#2322)
```

### git_turboprefill_hint

```text
none
```

### model_path

```text
/mnt/models/AI/LLM/Qwen3.8-27B-Q8_0.gguf
```

### model_filename

```text
Qwen3.8-27B-Q8_0.gguf
```

### model_size_bytes

```text
29047084352
```

### model_size_gib

```text
27.052
```

### gguf_architecture

```text
qwen35
```

### gguf_tensor_count

```text
866
```

### gguf_tensor_types

```text
F32:360, Q8_0:506
```

### model_sha256

```text
disabled (MODEL_HASH=0)
```

### TurboPrefill runtime markers

```text
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=4097 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=4097 requested_outputs=4097 logits_mib=3880.95 embd_mib=80.02 buf_used_mib=3960.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=4097 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=4097 requested_outputs=4097 logits_mib=3880.95 embd_mib=80.02 buf_used_mib=3960.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=654 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=654 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=654 requested_outputs=654 logits_mib=619.51 embd_mib=12.77 buf_used_mib=632.29 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=654 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
    "prompt": "Read the following text.\n\nAfter reaching the end of the text, output 100 numbered lines.\n\nEach line must contain at least two words.\n\nDo not provide any explanations.\n\nBeginning of the text:\nTurboPrefill is a Proof-of-Concept implementation of Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill.\n\nFor a detailed architectural discussion, see: RFC: Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\n\nMulti-GPU prefill acceleration for llama.cpp.\n\nThis repository contains a file overlay for llama.cpp and helper scripts for running llama-server benchmarks.\n\nHow TurboPrefill Was Created\nFor more than 20 years, I worked on the design, construction, and optimization of custom industrial production lines and control systems.\n\nWhile experimenting with running local AI models using llama.cpp on multi-GPU systems in layer-split mode, I noticed a well-known characteristic of long-context prefill execution.\n\nIn layer-split mode, the model is distributed across multiple GPUs by layers. Under the standard execution path, each ubatch passes sequentially through all model layers. As a result, some GPUs remain idle while waiting for the previous ubatch to complete processing through the remaining layers.\n\nWhile analyzing the scheduler's behavior,End of the text. Start your response.\n",
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=263 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=263 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=263 requested_outputs=263 logits_mib=249.13 embd_mib=5.14 buf_used_mib=254.27 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=263 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
    "prompt": "Read the following text.\n\nAfter reaching the end of the text, output 100 numbered lines.\n\nEach line must contain at least two words.\n\nDo not provide any explanations.\n\nBeginning of the text:\n\nRFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\n#24219\nOpen\nsergey-automation\nwants to merge 1 commit into\nggml-org:master\nfrom\nsergey-automation:turboprefill-rfc-poc\n+862\n-16\nLines changed: 862 additions & 16 deletions\nConversation1 (1)\nCommits1 (1)\nChecks1 (1)\nFiles changed5 (5)\nOpen\n[RFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill#24219\nsergey-automation\nwants to merge 1 commit into\nggml-org:master\nfrom\nsergey-automation:turboprefill-rfc-poc\nConversation\n@sergey-automation\nsergey-automation\ncommented\n3 weeks ago\n[RFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\n1. Status: Proof of Concept (PoC)\nThis RFC describes an experimental scheduling mechanism implemented in the TurboPrefill project and intended for discussion of the architectural approach.\n\n2. The Problem\nWith split_mode = layer, processing of a single request during the prefill phase is performed by passing each ubatch sequentially through the GPU pipeline.\n\nWhen processing a single ubatch, GPU stages are utilized sequentially: early GPUs become idle after completing their work, while later GPUs remain idle waiting for input data.\n\nThis limits GPU utilization efficiency and reduces performance scaling as the number of devices increases.\n\n3. Proposed Approach\nWithin the scope of this RFC, the term Intra-Prompt Pipeline Scheduling refers to the request-internal scheduling mechanism for the prefill phase described below.\n\nThe proposed approach does not modify the division of a request into ubatch units.\n\nDuring the prefill phase, ubatch instances are pre-classified. ubatch instances requiring the standard execution order continue to be processed by the existing scheduling mechanism. ubatch instances suitable for pipeline execution are routed to the Intra-Prompt Pipeline Scheduling mode implemented in TurboPrefill.\n\nIn this mode, ubatch instances are accumulated until the final ubatch of the current batch is received, after which they are executed sequentiallyEnd of the text. Start your response.\n",
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=536 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=536 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=536 requested_outputs=536 logits_mib=507.73 embd_mib=10.47 buf_used_mib=518.20 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=536 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
    "prompt": "Read the following text.\n\nAfter reaching the end of the text, output 100 numbered lines.\n\nEach line must contain at least two words.\n\nDo not provide any explanations.\n\nBeginning of the text:\nHow a Sawmill Helped Speed Up AI.\n\nFor more than 20 years I have been finding and eliminating bottlenecks in factories, production lines, machine tools, and automation systems.\n\nIn industry, I often saw that system performance is determined not only by the power of individual units, but also by how the workflow between them is organized.\n\nRecently, I was simply playing with an old mining rig built from 10 NVIDIA P104-100 GPUs.\n\nI ran GPT-OSS-120B on it using llama.cpp.\n\nWhile watching GPU utilization, I noticed a strange picture. Despite having ten GPUs, at any given moment only one GPU was doing most of the work, while the others were waiting for their turn.\n\nThis looked surprisingly familiar.\n\nI had seen something similar on one of my sawmill production lines, where a log passes through several machines sequentially: while one machine is working, the rest of the line sits idle.\n\nJust like on the sawmill line, I decided to feed the \"tree trunks\" more densely.\n\nBut first, a little theory.\n\nllama.cpp has a mode that splits a model across multiple GPUs by layers. This makes it possible to distribute a large model across the VRAM of several GPUs when a single GPU does not have enough memory.\n\nEach GPU processes its own part of the data and then passes the already \"chewed\" data to the next GPU. It is important that the data passes through the layers strictly in sequence — from the first layer to the last. Later data must not overtake earlier data.\n\nContinuing the sawmill analogy, the next tree trunk had to wait until the previous tree trunk passed through every machine in the line.\n\nFor the \"decode\" stage this is indeed a necessary condition — generating the next token requires the previous one.\n\nFor the \"prefill\" stage, however, this is not necessary. A tree trunk can be fed into a machine as soon as the previous tree trunk has cleared that machine, without waiting for it to pass through all the remaining machines in the line. The only requirement is to preserve the correct order.\n\nThis is how TurboPrefill was born — a mechanism called \"Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\".\n\nTo avoid breaking existing mechanisms, I added two things to llama.cpp:\n\n1. A \"sorting table\" that selects and accumulates suitable \"tree trunks\" (micro-batches (UB) belonging to a batch (B)).\n2. A separate turbo pipeline into which \"tree trunks\" can be fed more densely.\n\nThe difference from the standard pipeline is that each machine has its own table where a tree trunk can sit and wait until the machine becomes available.\n\nIn the standard pipeline there is only one table shared by all GPUs, and it effectively \"runs\" from machine to machine as the tree trunk progresses through the line.\n\n\"Tree trunks\" that did not meet the required conditions were sent to the regular pipeline.\n\nIn the first implementation:\n\nGitHub repository: sergey-automation/TurboPrefill \n\nI used strict selection criteria and only accepted \"tree trunks containing text data only\".\n\nIn the next implementation:\n\nGitHub repository: sergey-automation/TurboPrefill-VLM-Validation\n\nI relaxed the selection criteria and, in addition to text data, started accepting \"visual\" data as well — situations where a user uploads an image (or screenshot) and asks the AI to answer questions about it.\n\nAs a result, the responsiveness of AI interactions improved significantly. The waiting time between asking a question and receiving the beginning of an answer was reduced by 1.6× for two-GPU pipelines and by up to 2.2× for eight-GPU pipelines.\n\nFor example, if you upload a screenshot of an error and ask how to fix it, or upload a document and ask for a brief explanation of its contents, TurboPrefill allows the answer to begin several seconds sooner. The larger the document, image, or request, the greater the time savings compared to the standard pipeline.\n\nThe speedup is achieved entirely through scheduling. The mathematics and logic of the model remain unchanged and do not affect answer quality.\n\nThe mechanism itself is not tied to any particular GPU architecture. It has been tested on several GPU generations — from Pascal (GTX 1080, P104-100) to Ampere (RTX 3090) and Blackwell (RTX 5060 Ti).\n\nI proposed, introduced, and described the \"Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\" mechanism here:\nhttps://github.com/ggml-org/llama.cpp/pull/24219\n\nAnd created several implementations:\n\nGitHub repository: sergey-automation/TurboPrefill \n\nGitHub repository: sergey-automation/TurboPrefill-VLM-Validation\n\nEnd of the text. Start your response.\n",
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=1077 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1077 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1077 requested_outputs=1077 logits_mib=1020.21 embd_mib=21.04 buf_used_mib=1041.24 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=1077 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=2325 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=2325 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=2325 requested_outputs=2325 logits_mib=2202.39 embd_mib=45.41 buf_used_mib=2247.80 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=2325 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=4097 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=4097 requested_outputs=4097 logits_mib=3880.95 embd_mib=80.02 buf_used_mib=3960.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=3960.97
llama_decode_internal: TurboPrefill requested=0 active=0 n_tokens=186 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=186 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=186 requested_outputs=186 logits_mib=176.19 embd_mib=3.63 buf_used_mib=179.82 buf_alloc_mib=3960.97
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q8_0.gguf --host 0.0.0.0 --port 8081 -ngl 999 -c 260000 --override-kv llama.context_length=int:260000 -b 4097 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer --minilog -ts 9/11/11/11/11/11/9 --flash-attn auto --no-warmup --mmproj /mnt/models/AI/LLM/Qwen3.8-27B-mmproj-BF16.gguf --spec-type mtp:n_max=3
```

Server PID: `5162`  
Stop command: `kill -INT 5162`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Decode time s | Wall s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 65.67 | 4.08 | 12.99 | 9.86 | 18.39 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 79.11 | 6.84 | 13.48 | 9.50 | 18.27 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 87.94 | 12.30 | 11.59 | 11.04 | 25.40 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 68.09 | 34.22 | 10.62 | 12.05 | 48.54 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 62.33 | 68.79 | 10.55 | 12.13 | 84.16 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 68.22 | 129.76 | 10.94 | 11.70 | 159.46 |
| ctx_016384.txt | 1 | 1 | 17670 | 128 | 55.16 | 320.36 | 9.30 | 13.77 | 339.72 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 7.0 | 7.0 | 51.8 | 51.8 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 53.0 | 53.0 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 51.5 | 51.5 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 54.8 | 54.8 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 53.4 | 53.4 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 8.0 | 8.0 | 50.8 | 50.8 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 83.0 | 83.0 | 48.2 | 48.2 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 9.4 | 25.0 | 61.9 | 119.2 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 9.0 | 15.0 | 56.7 | 76.6 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 8.9 | 16.0 | 66.6 | 150.2 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 12.1 | 42.0 | 78.3 | 185.6 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 24.1 | 78.0 | 59.8 | 92.3 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 14.4 | 26.0 | 67.6 | 150.2 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 36.7 | 100.0 | 74.6 | 138.3 | 6535 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 8.3 | 25.0 | 59.6 | 75.5 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 24.7 | 28.0 | 85.9 | 151.3 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 16.7 | 28.0 | 51.8 | 52.0 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 18.7 | 28.0 | 55.6 | 57.4 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 11.3 | 18.0 | 98.7 | 183.9 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 89.4 | 166.1 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 46.3 | 100.0 | 54.9 | 56.4 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 3.6 | 13.0 | 90.5 | 149.5 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 8.6 | 15.0 | 67.9 | 96.9 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 7.0 | 15.0 | 51.9 | 52.1 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 7.2 | 15.0 | 54.6 | 56.0 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 22.2 | 49.0 | 57.4 | 67.3 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 15.4 | 39.0 | 66.4 | 108.8 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 17.0 | 34.0 | 81.6 | 115.5 | 6535 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 24.4 | 26.0 | 74.3 | 163.7 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 5.6 | 28.0 | 62.3 | 77.3 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 13.4 | 31.0 | 98.1 | 157.7 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 7.2 | 29.0 | 76.1 | 160.2 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 19.2 | 31.0 | 79.3 | 184.3 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 31.6 | 52.0 | 51.3 | 53.2 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 38.6 | 53.0 | 58.5 | 75.5 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 12.0 | 24.0 | 52.0 | 52.4 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 14.3 | 16.0 | 53.9 | 55.4 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 14.7 | 19.0 | 54.3 | 61.8 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 12.0 | 15.0 | 64.7 | 91.0 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 11.2 | 29.0 | 97.1 | 159.8 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 7.8 | 14.0 | 92.4 | 161.0 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 43.8 | 80.0 | 83.0 | 148.9 | 6535 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 10.1 | 31.0 | 55.7 | 109.7 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 8.1 | 34.0 | 58.0 | 152.3 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 11.8 | 39.0 | 51.8 | 113.1 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 10.0 | 32.0 | 67.3 | 172.7 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 17.8 | 84.0 | 49.7 | 116.8 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 12.6 | 35.0 | 45.8 | 67.4 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 40.0 | 86.0 | 72.8 | 167.1 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 11.5 | 15.0 | 56.0 | 104.6 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 11.2 | 16.0 | 47.4 | 47.5 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 11.5 | 17.0 | 50.7 | 51.5 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 14.2 | 20.0 | 55.5 | 62.4 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 9.8 | 31.0 | 58.8 | 91.9 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 11.8 | 56.0 | 72.8 | 117.8 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 27.2 | 39.0 | 81.6 | 145.7 | 6535 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 12.1 | 36.0 | 48.1 | 104.1 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 6.4 | 37.0 | 54.4 | 113.6 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 10.1 | 41.0 | 55.0 | 178.3 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 12.0 | 39.0 | 59.3 | 159.9 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 17.1 | 40.0 | 49.6 | 112.2 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 15.5 | 43.0 | 49.5 | 104.2 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 40.9 | 99.0 | 61.5 | 135.9 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 19.1 | 66.0 | 52.9 | 85.4 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 14.6 | 37.0 | 63.6 | 142.5 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 15.5 | 42.0 | 53.1 | 61.9 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 13.6 | 37.0 | 63.7 | 108.7 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 12.0 | 18.0 | 79.3 | 164.0 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 8.9 | 16.0 | 52.4 | 95.2 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 21.6 | 41.0 | 73.3 | 135.0 | 6535 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 14.0 | 66.0 | 54.4 | 119.8 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 14.5 | 42.0 | 59.5 | 170.5 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 18.3 | 53.0 | 66.3 | 174.3 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 16.2 | 51.0 | 71.6 | 187.0 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 11.6 | 44.0 | 64.2 | 174.2 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 9.8 | 47.0 | 59.4 | 168.3 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 45.7 | 100.0 | 67.3 | 181.0 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 10.8 | 42.0 | 52.9 | 71.6 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 17.2 | 45.0 | 62.2 | 159.8 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 17.8 | 56.0 | 69.1 | 169.8 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 13.7 | 53.0 | 67.2 | 161.0 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 10.6 | 30.0 | 98.4 | 180.1 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 10.9 | 38.0 | 50.9 | 51.9 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 38.9 | 99.0 | 66.0 | 127.7 | 6535 |

### ctx_016384.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 10.5 | 58.0 | 60.8 | 170.1 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 11.7 | 66.0 | 64.3 | 181.8 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 17.7 | 73.0 | 61.5 | 177.9 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 17.0 | 74.0 | 72.4 | 190.8 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 12.3 | 98.0 | 69.7 | 182.0 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 15.7 | 74.0 | 61.5 | 173.4 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 35.9 | 100.0 | 63.8 | 183.1 | 6535 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 5.9 | 19.0 | 55.6 | 98.5 | 7191 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 6.4 | 20.0 | 61.8 | 114.0 | 6143 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 4.2 | 24.0 | 66.5 | 138.4 | 7535 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 5.7 | 22.0 | 70.1 | 160.4 | 7135 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 19.4 | 61.0 | 54.7 | 63.8 | 6545 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 14.3 | 31.0 | 59.8 | 93.0 | 6735 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 28.3 | 96.0 | 74.3 | 117.0 | 6535 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 28.6 %, max 28.6 %

RAM used: avg 13660 MiB, max 13660 MiB, avg 86.0 %, max 86.0 %

Swap used: avg 636 MiB, max 636 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.1 | 99.1 |
| 1 | 3.3 | 3.3 |
| 2 | 7.6 | 7.6 |
| 3 | 2.8 | 2.8 |

Decode stage:

CPU total: avg 27.5 %, max 28.1 %

RAM used: avg 13318 MiB, max 13671 MiB, avg 83.9 %, max 86.1 %

Swap used: avg 636 MiB, max 636 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 98.5 | 100.0 |
| 1 | 3.3 | 4.8 |
| 2 | 4.5 | 5.7 |
| 3 | 3.4 | 5.2 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 28.4 %, max 29.1 %

RAM used: avg 13939 MiB, max 13946 MiB, avg 87.8 %, max 87.8 %

Swap used: avg 635 MiB, max 635 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 98.6 | 100.0 |
| 1 | 5.1 | 6.2 |
| 2 | 4.1 | 4.8 |
| 3 | 4.9 | 6.2 |

Decode stage:

CPU total: avg 27.8 %, max 28.2 %

RAM used: avg 13952 MiB, max 13963 MiB, avg 87.9 %, max 88.0 %

Swap used: avg 635 MiB, max 635 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 100.0 | 100.0 |
| 1 | 4.0 | 7.1 |
| 2 | 2.9 | 4.7 |
| 3 | 3.8 | 5.6 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 28.7 %, max 29.0 %

RAM used: avg 14500 MiB, max 14506 MiB, avg 91.3 %, max 91.4 %

Swap used: avg 638 MiB, max 638 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 100.0 | 100.0 |
| 1 | 4.7 | 6.6 |
| 2 | 4.1 | 5.7 |
| 3 | 5.4 | 6.6 |

Decode stage:

CPU total: avg 28.4 %, max 31.3 %

RAM used: avg 14394 MiB, max 14482 MiB, avg 90.7 %, max 91.2 %

Swap used: avg 638 MiB, max 639 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 100.0 | 100.0 |
| 1 | 6.2 | 12.0 |
| 2 | 2.8 | 7.1 |
| 3 | 3.7 | 5.7 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 26.9 %, max 30.9 %

RAM used: avg 14819 MiB, max 14963 MiB, avg 93.3 %, max 94.3 %

Swap used: avg 638 MiB, max 638 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 34.8 | 100.0 |
| 1 | 8.6 | 11.9 |
| 2 | 6.6 | 8.6 |
| 3 | 57.0 | 100.0 |

Decode stage:

CPU total: avg 27.2 %, max 29.0 %

RAM used: avg 14961 MiB, max 14985 MiB, avg 94.2 %, max 94.4 %

Swap used: avg 649 MiB, max 651 MiB, avg 2.6 %, max 2.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 92.0 | 100.0 |
| 1 | 5.4 | 7.7 |
| 2 | 2.8 | 4.3 |
| 3 | 7.7 | 27.0 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 26.6 %, max 42.9 %

RAM used: avg 14934 MiB, max 15721 MiB, avg 94.1 %, max 99.0 %

Swap used: avg 1098 MiB, max 1474 MiB, avg 4.5 %, max 6.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 14.3 | 96.3 |
| 1 | 49.6 | 100.0 |
| 2 | 7.6 | 19.5 |
| 3 | 34.5 | 100.0 |

Decode stage:

CPU total: avg 28.4 %, max 30.2 %

RAM used: avg 14572 MiB, max 14604 MiB, avg 91.8 %, max 92.0 %

Swap used: avg 1583 MiB, max 1643 MiB, avg 6.4 %, max 6.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 5.3 | 8.4 |
| 1 | 5.7 | 6.8 |
| 2 | 5.2 | 8.1 |
| 3 | 96.6 | 100.0 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 27.6 %, max 41.9 %

RAM used: avg 14171 MiB, max 15155 MiB, avg 89.3 %, max 95.5 %

Swap used: avg 1701 MiB, max 2495 MiB, avg 6.9 %, max 10.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 53.1 | 100.0 |
| 1 | 14.0 | 99.5 |
| 2 | 32.5 | 100.0 |
| 3 | 10.1 | 88.2 |

Decode stage:

CPU total: avg 27.2 %, max 28.9 %

RAM used: avg 14481 MiB, max 14643 MiB, avg 91.2 %, max 92.2 %

Swap used: avg 1610 MiB, max 1613 MiB, avg 6.6 %, max 6.6 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 3.7 | 6.2 |
| 1 | 5.2 | 7.2 |
| 2 | 4.1 | 9.5 |
| 3 | 95.1 | 100.0 |

### ctx_016384.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 28.6 %, max 35.6 %

RAM used: avg 14126 MiB, max 15713 MiB, avg 89.0 %, max 99.0 %

Swap used: avg 3154 MiB, max 3705 MiB, avg 12.8 %, max 15.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 49.8 | 100.0 |
| 1 | 28.3 | 100.0 |
| 2 | 13.5 | 100.0 |
| 3 | 22.2 | 100.0 |

Decode stage:

CPU total: avg 29.5 %, max 35.1 %

RAM used: avg 13521 MiB, max 13715 MiB, avg 85.2 %, max 86.4 %

Swap used: avg 4040 MiB, max 4049 MiB, avg 16.4 %, max 16.5 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 6.2 | 13.3 |
| 1 | 25.1 | 100.0 |
| 2 | 5.2 | 12.4 |
| 3 | 80.6 | 100.0 |

