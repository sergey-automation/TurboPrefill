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
- TURBOPREFILL: `1`
- TurboPrefill status: `active (TURBOPREFILL=1)`
- TurboPrefill version: `TurboPrefill:`
- llama.cpp git describe: `t0002-1026-g8337e4cd-dirty`
- llama.cpp git commit: `8337e4cd3861406fc04e0854b1409cd1b027fbc9`
- Server PID: `13589`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `active_slots=1..PARALLEL`
- Metrics policy: `server per-request timings only; no combined throughput calculated`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/bench_reports_Qwen3.8-27B-Q8_0_ik_1708/20260818_153045/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
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
CPU(s) scaling MHz:                      21%
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
Память:         15Gi        14Gi       395Mi       155Mi       1.1Gi       1.0Gi
Подкачка:       23Gi       5.6Gi        18Gi
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
srv    load_model: TurboPrefill: CUDA Graphs disabled for target and draft contexts
llama_init_from_model: TurboPrefill MTP compact output preallocation: logits_rows=129 embd_rows=4097 size=202.22 MiB
llama_init_from_model: TurboPrefill MTP compact output preallocation: logits_rows=129 embd_rows=4097 size=202.22 MiB
llama_decode_internal: TurboPrefill requested=1 active=1 n_tokens=4097 n_ubatch=32 full_ubatches=128 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=129 n_seq_max=1 causal=1 compact_mtp=1 n_outputs_embd=4097 requested_outputs=4097 logits_mib=122.20 embd_mib=80.02 buf_used_mib=202.22 buf_alloc_mib=202.22
turboprefill: version=ik_llama.cpp_8337e4cd_v6.5 accumulation_us=12286096 compute_us=8477746 total_us=20763842
llama_decode_internal: TurboPrefill requested=1 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=202.22
llama_decode_internal: TurboPrefill requested=1 active=1 n_tokens=4097 n_ubatch=32 full_ubatches=128 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=129 n_seq_max=1 causal=1 compact_mtp=1 n_outputs_embd=4097 requested_outputs=4097 logits_mib=122.20 embd_mib=80.02 buf_used_mib=202.22 buf_alloc_mib=202.22
turboprefill: version=ik_llama.cpp_8337e4cd_v6.5 accumulation_us=2436664 compute_us=10727952 total_us=13164616
llama_decode_internal: TurboPrefill requested=1 active=0 n_tokens=4097 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=202.22
llama_decode_internal: TurboPrefill requested=1 active=1 n_tokens=654 n_ubatch=32 full_ubatches=20 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=21 n_seq_max=1 causal=1 compact_mtp=1 n_outputs_embd=654 requested_outputs=654 logits_mib=19.89 embd_mib=12.77 buf_used_mib=32.67 buf_alloc_mib=202.22
turboprefill: version=ik_llama.cpp_8337e4cd_v6.5 accumulation_us=207429 compute_us=2294983 total_us=2502412
llama_decode_internal: TurboPrefill requested=1 active=0 n_tokens=654 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=202.22
    "prompt": "Read the following text.\n\nAfter reaching the end of the text, output 100 numbered lines.\n\nEach line must contain at least two words.\n\nDo not provide any explanations.\n\nBeginning of the text:\nTurboPrefill is a Proof-of-Concept implementation of Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill.\n\nFor a detailed architectural discussion, see: RFC: Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\n\nMulti-GPU prefill acceleration for llama.cpp.\n\nThis repository contains a file overlay for llama.cpp and helper scripts for running llama-server benchmarks.\n\nHow TurboPrefill Was Created\nFor more than 20 years, I worked on the design, construction, and optimization of custom industrial production lines and control systems.\n\nWhile experimenting with running local AI models using llama.cpp on multi-GPU systems in layer-split mode, I noticed a well-known characteristic of long-context prefill execution.\n\nIn layer-split mode, the model is distributed across multiple GPUs by layers. Under the standard execution path, each ubatch passes sequentially through all model layers. As a result, some GPUs remain idle while waiting for the previous ubatch to complete processing through the remaining layers.\n\nWhile analyzing the scheduler's behavior,End of the text. Start your response.\n",
llama_decode_internal: TurboPrefill requested=1 active=1 n_tokens=263 n_ubatch=32 full_ubatches=8 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=9 n_seq_max=1 causal=1 compact_mtp=1 n_outputs_embd=263 requested_outputs=263 logits_mib=8.53 embd_mib=5.14 buf_used_mib=13.66 buf_alloc_mib=202.22
turboprefill: version=ik_llama.cpp_8337e4cd_v6.5 accumulation_us=116196 compute_us=650800 total_us=766996
llama_decode_internal: TurboPrefill requested=1 active=0 n_tokens=263 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=202.22
    "prompt": "Read the following text.\n\nAfter reaching the end of the text, output 100 numbered lines.\n\nEach line must contain at least two words.\n\nDo not provide any explanations.\n\nBeginning of the text:\n\nRFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\n#24219\nOpen\nsergey-automation\nwants to merge 1 commit into\nggml-org:master\nfrom\nsergey-automation:turboprefill-rfc-poc\n+862\n-16\nLines changed: 862 additions & 16 deletions\nConversation1 (1)\nCommits1 (1)\nChecks1 (1)\nFiles changed5 (5)\nOpen\n[RFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill#24219\nsergey-automation\nwants to merge 1 commit into\nggml-org:master\nfrom\nsergey-automation:turboprefill-rfc-poc\nConversation\n@sergey-automation\nsergey-automation\ncommented\n3 weeks ago\n[RFC][PoC] Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill\n1. Status: Proof of Concept (PoC)\nThis RFC describes an experimental scheduling mechanism implemented in the TurboPrefill project and intended for discussion of the architectural approach.\n\n2. The Problem\nWith split_mode = layer, processing of a single request during the prefill phase is performed by passing each ubatch sequentially through the GPU pipeline.\n\nWhen processing a single ubatch, GPU stages are utilized sequentially: early GPUs become idle after completing their work, while later GPUs remain idle waiting for input data.\n\nThis limits GPU utilization efficiency and reduces performance scaling as the number of devices increases.\n\n3. Proposed Approach\nWithin the scope of this RFC, the term Intra-Prompt Pipeline Scheduling refers to the request-internal scheduling mechanism for the prefill phase described below.\n\nThe proposed approach does not modify the division of a request into ubatch units.\n\nDuring the prefill phase, ubatch instances are pre-classified. ubatch instances requiring the standard execution order continue to be processed by the existing scheduling mechanism. ubatch instances suitable for pipeline execution are routed to the Intra-Prompt Pipeline Scheduling mode implemented in TurboPrefill.\n\nIn this mode, ubatch instances are accumulated until the final ubatch of the current batch is received, after which they are executed sequentiallyEnd of the text. Start your response.\n",
llama_decode_internal: TurboPrefill requested=1 active=1 n_tokens=536 n_ubatch=32 full_ubatches=16 devices=12 split_mode=1 nextn_layers=1 mtp_op=0 embeddings=0 mtp=1 has_mtp=1 emb_gate=1 n_outputs=17 n_seq_max=1 causal=1 compact_mtp=1 n_outputs_embd=536 requested_outputs=536 logits_mib=16.10 embd_mib=10.47 buf_used_mib=26.57 buf_alloc_mib=202.22
turboprefill: version=ik_llama.cpp_8337e4cd_v6.5 accumulation_us=233219 compute_us=1065408 total_us=1298627
llama_decode_internal: TurboPrefill requested=1 active=0 n_tokens=536 n_ubatch=32 full_ubatches=0 devices=12 split_mode=1 nextn_layers=1 mtp_op=1 embeddings=1 mtp=1 has_mtp=1 emb_gate=1 n_outputs=1 n_seq_max=1 causal=1 compact_mtp=0 n_outputs_embd=1 requested_outputs=1 logits_mib=0.95 embd_mib=0.02 buf_used_mib=0.97 buf_alloc_mib=202.22
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_ik_llama.cpp_8337e4cd/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q8_0.gguf --host 0.0.0.0 --port 8081 -ngl 999 -c 260000 --override-kv llama.context_length=int:260000 -b 4097 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer --minilog -ts 9/11/11/11/11/11/9 --flash-attn auto --no-warmup --mmproj /mnt/models/AI/LLM/Qwen3.8-27B-mmproj-BF16.gguf --spec-type mtp:n_max=3
```

Server PID: `13589`  
Stop command: `kill -INT 13589`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Decode time s | Wall s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 111.26 | 2.41 | 12.60 | 10.16 | 17.01 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 175.48 | 3.08 | 13.43 | 9.53 | 14.54 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 254.62 | 4.25 | 11.59 | 11.05 | 17.36 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 278.08 | 8.38 | 10.51 | 12.18 | 22.82 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 294.97 | 14.54 | 10.75 | 11.90 | 29.15 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 272.30 | 32.51 | 11.26 | 11.37 | 52.22 |
| ctx_016384.txt | 1 | 1 | 17670 | 128 | 215.21 | 82.11 | 9.00 | 14.22 | 101.27 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 50.9 | 50.9 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 52.0 | 52.0 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 52.1 | 52.1 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 54.6 | 54.6 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 53.1 | 53.1 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 22.0 | 22.0 | 50.2 | 50.2 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 64.0 | 64.0 | 51.6 | 51.6 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 8.7 | 14.0 | 50.9 | 51.0 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 6.2 | 17.0 | 47.5 | 52.3 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 15.3 | 24.0 | 46.7 | 52.2 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 18.8 | 39.0 | 49.5 | 54.6 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 11.3 | 33.0 | 48.7 | 54.9 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 9.5 | 14.0 | 49.1 | 56.0 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 12.2 | 45.0 | 84.0 | 128.0 | 6525 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 24.0 | 24.0 | 51.0 | 51.0 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 28.0 | 28.0 | 52.2 | 52.2 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 28.0 | 28.0 | 52.0 | 52.0 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 23.0 | 23.0 | 54.9 | 54.9 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 31.0 | 31.0 | 55.5 | 55.5 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 117.0 | 117.0 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 108.2 | 108.2 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 12.6 | 21.0 | 50.2 | 55.6 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 25.2 | 75.0 | 73.3 | 153.6 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 10.0 | 16.0 | 57.4 | 75.5 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 10.0 | 16.0 | 81.6 | 165.0 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 7.8 | 17.0 | 75.2 | 162.0 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 10.6 | 14.0 | 50.3 | 50.8 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 18.0 | 46.0 | 68.0 | 123.9 | 6525 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 54.0 | 82.0 | 80.2 | 111.1 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 49.5 | 89.0 | 80.7 | 107.2 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 60.0 | 99.0 | 131.6 | 138.2 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 44.5 | 89.0 | 115.0 | 138.1 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 48.0 | 96.0 | 106.8 | 160.0 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 55.0 | 85.0 | 100.8 | 151.4 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 45.5 | 63.0 | 115.6 | 177.2 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 6.3 | 14.0 | 53.6 | 63.6 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 8.0 | 15.0 | 66.1 | 119.8 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 12.5 | 17.0 | 76.1 | 112.4 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 13.0 | 15.0 | 86.4 | 126.4 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 11.0 | 16.0 | 79.4 | 142.9 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 10.3 | 14.0 | 54.8 | 66.8 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 30.0 | 39.0 | 68.5 | 97.2 | 6525 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 43.3 | 81.0 | 108.2 | 147.8 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 37.3 | 88.0 | 122.4 | 160.9 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 33.0 | 99.0 | 118.1 | 170.9 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 30.7 | 92.0 | 93.0 | 169.2 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 55.7 | 96.0 | 97.4 | 185.3 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 36.7 | 83.0 | 88.5 | 165.1 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 34.0 | 61.0 | 74.3 | 124.1 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 4.7 | 14.0 | 63.7 | 99.1 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 6.4 | 14.0 | 84.2 | 169.7 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 10.3 | 19.0 | 53.8 | 102.9 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 10.6 | 17.0 | 51.8 | 71.0 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 21.6 | 67.0 | 67.2 | 176.4 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 21.6 | 65.0 | 62.0 | 111.6 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 35.9 | 47.0 | 65.1 | 105.0 | 6525 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 49.7 | 82.0 | 111.9 | 163.6 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 42.7 | 87.0 | 102.8 | 180.3 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 49.5 | 99.0 | 108.2 | 175.5 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 46.7 | 95.0 | 110.0 | 179.8 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 46.2 | 96.0 | 105.3 | 179.7 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 44.0 | 90.0 | 94.2 | 167.3 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 59.0 | 99.0 | 86.2 | 153.8 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 6.0 | 16.0 | 55.5 | 98.1 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 6.0 | 14.0 | 76.4 | 157.7 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 7.4 | 16.0 | 77.4 | 158.0 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 9.7 | 17.0 | 76.3 | 144.1 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 11.1 | 18.0 | 83.6 | 163.7 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 17.9 | 54.0 | 50.5 | 50.6 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 32.6 | 47.0 | 54.9 | 56.3 | 6525 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 45.9 | 82.0 | 94.3 | 167.2 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 42.7 | 89.0 | 95.5 | 168.7 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 49.2 | 99.0 | 109.1 | 181.8 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 49.2 | 95.0 | 104.0 | 187.4 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 48.3 | 96.0 | 101.6 | 192.3 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 56.0 | 99.0 | 93.2 | 156.8 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 41.4 | 82.0 | 91.2 | 172.9 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 14.6 | 79.0 | 60.7 | 109.5 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 15.1 | 78.0 | 63.9 | 132.3 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 25.4 | 99.0 | 68.1 | 149.1 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 16.1 | 64.0 | 95.5 | 162.7 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 12.2 | 19.0 | 72.6 | 130.3 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 10.3 | 17.0 | 71.7 | 151.5 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 35.9 | 99.0 | 72.7 | 115.8 | 6525 |

### ctx_016384.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 51.3 | 99.0 | 95.8 | 171.7 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 52.1 | 97.0 | 104.8 | 186.6 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 64.9 | 100.0 | 115.9 | 182.7 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 62.9 | 98.0 | 117.7 | 190.3 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 54.3 | 97.0 | 115.7 | 184.9 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 53.6 | 95.0 | 109.7 | 172.3 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 48.8 | 100.0 | 99.0 | 176.7 | 6525 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 6.6 | 19.0 | 58.5 | 117.4 | 7181 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 7.4 | 22.0 | 50.3 | 65.0 | 6133 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 16.1 | 61.0 | 52.7 | 93.3 | 7525 |
| 3 | NVIDIA P104-100 | Gen1 x1 | 21.6 | 74.0 | 62.4 | 110.9 | 7125 |
| 4 | NVIDIA P104-100 | Gen1 x1 | 18.6 | 84.0 | 71.4 | 183.6 | 6535 |
| 5 | NVIDIA P104-100 | Gen1 x1 | 21.6 | 95.0 | 63.8 | 158.8 | 6725 |
| 6 | NVIDIA P104-100 | Gen1 x1 | 49.3 | 99.0 | 73.8 | 130.2 | 6525 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 26.3 %, max 26.3 %

RAM used: avg 7064 MiB, max 7064 MiB, avg 44.5 %, max 44.5 %

Swap used: avg 1024 MiB, max 1024 MiB, avg 4.2 %, max 4.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 98.6 | 98.6 |
| 1 | 3.8 | 3.8 |
| 2 | 1.9 | 1.9 |
| 3 | 0.9 | 0.9 |

Decode stage:

CPU total: avg 28.0 %, max 30.2 %

RAM used: avg 6765 MiB, max 7074 MiB, avg 42.6 %, max 44.6 %

Swap used: avg 1024 MiB, max 1024 MiB, avg 4.2 %, max 4.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 36.0 | 100.0 |
| 1 | 67.1 | 100.0 |
| 2 | 4.8 | 8.0 |
| 3 | 3.8 | 7.1 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 26.5 %, max 26.5 %

RAM used: avg 7257 MiB, max 7257 MiB, avg 45.7 %, max 45.7 %

Swap used: avg 1023 MiB, max 1023 MiB, avg 4.2 %, max 4.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 2.8 | 2.8 |
| 1 | 100.0 | 100.0 |
| 2 | 1.4 | 1.4 |
| 3 | 1.9 | 1.9 |

Decode stage:

CPU total: avg 26.7 %, max 28.5 %

RAM used: avg 7189 MiB, max 7236 MiB, avg 45.3 %, max 45.6 %

Swap used: avg 1023 MiB, max 1023 MiB, avg 4.2 %, max 4.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 1.4 | 3.8 |
| 1 | 99.3 | 100.0 |
| 2 | 2.1 | 7.1 |
| 3 | 3.7 | 6.2 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 28.8 %, max 31.2 %

RAM used: avg 7637 MiB, max 7642 MiB, avg 48.1 %, max 48.1 %

Swap used: avg 1023 MiB, max 1023 MiB, avg 4.2 %, max 4.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 6.6 | 10.4 |
| 1 | 99.8 | 100.0 |
| 2 | 4.0 | 6.7 |
| 3 | 4.2 | 7.1 |

Decode stage:

CPU total: avg 26.6 %, max 27.6 %

RAM used: avg 7618 MiB, max 7640 MiB, avg 48.0 %, max 48.1 %

Swap used: avg 1021 MiB, max 1023 MiB, avg 4.2 %, max 4.2 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 39.4 | 100.0 |
| 1 | 63.4 | 100.0 |
| 2 | 1.3 | 4.2 |
| 3 | 2.0 | 4.2 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 26.6 %, max 34.1 %

RAM used: avg 8106 MiB, max 8190 MiB, avg 51.1 %, max 51.6 %

Swap used: avg 1013 MiB, max 1013 MiB, avg 4.1 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 88.8 | 100.0 |
| 1 | 6.8 | 13.5 |
| 2 | 6.1 | 12.3 |
| 3 | 4.2 | 10.4 |

Decode stage:

CPU total: avg 29.8 %, max 33.3 %

RAM used: avg 8048 MiB, max 8071 MiB, avg 50.7 %, max 50.8 %

Swap used: avg 1011 MiB, max 1013 MiB, avg 4.1 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 100.0 | 100.0 |
| 1 | 5.9 | 10.8 |
| 2 | 7.2 | 12.1 |
| 3 | 5.7 | 9.9 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 30.9 %, max 33.9 %

RAM used: avg 8760 MiB, max 8767 MiB, avg 55.2 %, max 55.2 %

Swap used: avg 1010 MiB, max 1010 MiB, avg 4.1 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.9 | 100.0 |
| 1 | 7.0 | 11.2 |
| 2 | 8.1 | 12.9 |
| 3 | 8.1 | 12.3 |

Decode stage:

CPU total: avg 26.8 %, max 27.5 %

RAM used: avg 8786 MiB, max 8799 MiB, avg 55.3 %, max 55.4 %

Swap used: avg 1010 MiB, max 1010 MiB, avg 4.1 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.9 | 100.0 |
| 1 | 2.7 | 5.7 |
| 2 | 2.6 | 3.8 |
| 3 | 1.5 | 3.8 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 30.7 %, max 35.6 %

RAM used: avg 8581 MiB, max 9855 MiB, avg 54.1 %, max 62.1 %

Swap used: avg 1009 MiB, max 1009 MiB, avg 4.1 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 15.6 | 100.0 |
| 1 | 8.0 | 15.8 |
| 2 | 91.6 | 100.0 |
| 3 | 7.2 | 15.2 |

Decode stage:

CPU total: avg 27.7 %, max 32.7 %

RAM used: avg 8570 MiB, max 8626 MiB, avg 54.0 %, max 54.3 %

Swap used: avg 1009 MiB, max 1009 MiB, avg 4.1 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 3.3 | 10.0 |
| 1 | 4.7 | 11.3 |
| 2 | 99.9 | 100.0 |
| 3 | 2.6 | 9.4 |

### ctx_016384.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 31.2 %, max 36.6 %

RAM used: avg 10092 MiB, max 10669 MiB, avg 63.6 %, max 67.2 %

Swap used: avg 1054 MiB, max 1057 MiB, avg 4.3 %, max 4.3 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 20.7 | 100.0 |
| 1 | 16.9 | 100.0 |
| 2 | 38.4 | 100.0 |
| 3 | 48.4 | 100.0 |

Decode stage:

CPU total: avg 29.3 %, max 33.8 %

RAM used: avg 10785 MiB, max 10821 MiB, avg 67.9 %, max 68.2 %

Swap used: avg 1057 MiB, max 1057 MiB, avg 4.3 %, max 4.3 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 63.1 | 100.0 |
| 1 | 5.8 | 12.2 |
| 2 | 41.2 | 100.0 |
| 3 | 6.4 | 13.4 |

