# llama-server fixed-parallel context benchmark report

## Test header

- MODEL: `/mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf`
- NGL: `999`
- CTX_SIZE: `17000`
- N_GEN: `128`
- BATCH: `4096`
- UBATCH: `32`
- CTK: `f16`
- CTV: `f16`
- SPEC_TYPE: `draft-mtp`
- SPEC_DRAFT_N_MAX: `3`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.15`
- CACHE_PROMPT: `0`
- FLASH_ATTN: `auto`
- THREADS: `auto`
- THREADS_BATCH: `auto`
- REPEATS: `1`
- CUDA_VISIBLE_DEVICES: `0,1,2`
- TURBOPREFILL: `1`
- TurboPrefill status: `active (TURBOPREFILL=1)`
- TurboPrefill version: `TurboPrefill_llama.cpp_b11429_v2.2m:`
- llama.cpp git describe: `v0.6.0-dirty`
- llama.cpp git commit: `d81235049384534c167caea52b85a694f6103d14`
- Server PID: `84711`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `PARALLEL=N => exactly N slots and N concurrent requests; request i is pinned to server slot i`
- Metrics policy: `server timings preserved + independent client first-token/wall timings + interval-union aggregate throughput`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/bench_reports_Qwen3.8-27B-Q4_K_M/20261011_211738/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
```

### RUN_DIR

```text
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m
```

### CONFIG_PATH

```text
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/config_Qwen_3.8.sh
```

### LLAMA_SERVER_BIN

```text
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/build/bin/llama-server
```

### LOCAL_LD_LIBRARY_PATH

```text
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/build/bin
```

### CUDA_VISIBLE_DEVICES_effective

```text
0,1,2
```

### selected_gpu_count

```text
3
```

### selected_gpu_models

```text
NVIDIA P104-100 x3
```

### llama_server_version

```text
version: 0.6.0-dev (build 11429, commit d81235049)
built with GNU 13.3.0 for Linux x86_64
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
Память:         15Gi       920Mi       6.3Gi        41Mi       8.6Gi        14Gi
Подкачка:       23Gi       423Mi        23Gi
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
v0.6.0-dirty
```

### git_commit

```text
d81235049384534c167caea52b85a694f6103d14
```

### git_last_commit

```text
2026-10-05 18:13:51 +0300
llama.cpp : bump version to 0.6.0 (#29997)
```

### git_turboprefill_hint

```text
none
```

### model_path

```text
/mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf
```

### model_filename

```text
Qwen3.8-27B-Q4_K_M.gguf
```

### model_size_bytes

```text
16810714432
```

### model_size_gib

```text
15.656
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
F32:360, Q4_K:439, Q6_K:67
```

### model_sha256

```text
disabled (MODEL_HASH=0)
```

### TurboPrefill runtime markers

```text
0.00.432.009 I srv    load_model: TurboPrefill_llama.cpp_b11429_v2.2m: CUDA Graphs disabled for target and draft contexts
0.57.687.572 I load_tensors: TurboPrefill_llama.cpp_b11429_v2.2m: parallel GPU weight loading active: 3 layer-split worker(s)
1.52.428.776 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=4096 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=128 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
1.52.647.563 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=127
2.14.235.017 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=1574472 compute_us=19406305 total_us=20980777
2.14.936.525 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.18.284.644 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=4096 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=128 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.18.284.663 I process_ubatch: TurboPrefill recurrent rs_z=-1 first_ubatch=turbo turbo_ubatches=128
2.37.899.740 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=909065 compute_us=18689138 total_us=19598203
2.38.535.157 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.40.532.480 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=625 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=19 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.40.532.494 I process_ubatch: TurboPrefill recurrent rs_z=-1 first_ubatch=turbo turbo_ubatches=19
2.43.781.644 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=130156 compute_us=3116172 total_us=3246328
2.44.169.592 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.01.441.656 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=232 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=7 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.01.441.671 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=6
3.02.909.447 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=400489 compute_us=1045057 total_us=1445546
3.03.230.461 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.16.735.517 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=505 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=15 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.16.735.529 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=14
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf --host 0.0.0.0 --port 8081 -lv 4 -ngl 999 -c 17000 --override-kv llama.context_length=int:17000 -b 4096 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer --parallel-load -ts 1/1/1 --flash-attn auto --no-warmup --no-mmproj --spec-type draft-mtp --spec-draft-n-max 3
```

Server PID: `84711`  
Stop command: `kill -INT 84711`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Server prefill tok/s | Server prefill s | Server decode tok/s | Server decode s | Client prefill~ s | Client decode~ s | Client wall s | Group wall s | Group prefill tok/s | Group decode tok/s | Group prefill+decode tok/s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 65.08 | 4.12 | 12.83 | 9.90 | 8.65 | 9.91 | 18.56 | 18.56 | 30.97 | 12.92 | 21.34 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 100.69 | 5.37 | 13.49 | 9.42 | 6.60 | 9.43 | 16.03 | 16.03 | 81.94 | 13.57 | 41.72 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 135.76 | 7.97 | 11.39 | 11.15 | 9.36 | 11.17 | 20.53 | 20.53 | 115.59 | 11.46 | 58.93 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 164.04 | 14.20 | 12.82 | 9.91 | 15.82 | 9.96 | 25.79 | 25.79 | 147.26 | 12.85 | 95.32 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 176.60 | 24.28 | 12.29 | 10.33 | 26.32 | 10.51 | 36.83 | 36.83 | 162.90 | 12.18 | 119.90 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 0.00 | 0.00 | 0.00 | 0.00 | 55.50 | 9.51 | 65.01 | 65.01 | 159.53 | 13.46 | 138.15 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 51.4 | 51.4 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 52.4 | 52.4 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 100.0 | 100.0 | 50.7 | 50.7 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 17.1 | 32.0 | 52.2 | 96.1 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 19.6 | 56.0 | 74.5 | 149.7 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 69.9 | 99.0 | 62.4 | 86.6 | 6459 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 50.0 | 100.0 | 51.1 | 59.9 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 48.0 | 96.0 | 61.0 | 79.5 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 90.5 | 95.0 | 71.8 | 98.6 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 25.0 | 32.0 | 44.3 | 55.0 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 12.6 | 27.0 | 74.0 | 118.3 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 61.2 | 68.0 | 87.3 | 204.9 | 6459 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 54.3 | 100.0 | 77.2 | 99.1 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 51.3 | 96.0 | 96.7 | 105.7 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 51.0 | 78.0 | 44.7 | 47.9 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 35.0 | 99.0 | 59.5 | 118.8 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 26.2 | 31.0 | 69.5 | 126.4 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 52.3 | 67.0 | 67.2 | 130.5 | 6459 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 66.7 | 100.0 | 76.4 | 104.9 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 63.7 | 98.0 | 75.3 | 97.3 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 83.0 | 98.0 | 77.7 | 98.7 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 32.2 | 99.0 | 50.2 | 74.0 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 18.8 | 32.0 | 67.5 | 130.1 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 44.0 | 69.0 | 54.5 | 94.4 | 6459 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 79.8 | 100.0 | 80.5 | 104.9 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 76.7 | 97.0 | 87.6 | 134.2 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 87.4 | 98.0 | 78.0 | 99.8 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 25.5 | 34.0 | 57.4 | 125.0 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 25.8 | 39.0 | 50.6 | 86.6 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 48.0 | 69.0 | 59.9 | 90.1 | 6459 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 71.9 | 100.0 | 70.5 | 104.7 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 65.8 | 99.0 | 73.5 | 103.9 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 71.3 | 98.0 | 78.1 | 106.7 | 6459 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 24.5 %, max 24.5 %

RAM used: avg 4393 MiB, max 4393 MiB, avg 27.7 %, max 27.7 %

Swap used: avg 698 MiB, max 698 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 88.7 | 88.7 |
| 1 | 7.0 | 7.0 |
| 2 | 0.0 | 0.0 |
| 3 | 2.8 | 2.8 |

Decode stage:

CPU total: avg 31.9 %, max 34.4 %

RAM used: avg 4357 MiB, max 4411 MiB, avg 27.4 %, max 27.8 %

Swap used: avg 698 MiB, max 698 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 59.1 | 100.0 |
| 1 | 8.1 | 12.1 |
| 2 | 9.6 | 15.9 |
| 3 | 50.6 | 100.0 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 31.6 %, max 35.2 %

RAM used: avg 4815 MiB, max 4820 MiB, avg 30.3 %, max 30.4 %

Swap used: avg 698 MiB, max 698 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 11.2 | 16.4 |
| 1 | 97.7 | 100.0 |
| 2 | 8.6 | 11.5 |
| 3 | 9.0 | 13.2 |

Decode stage:

CPU total: avg 33.0 %, max 34.5 %

RAM used: avg 4832 MiB, max 4848 MiB, avg 30.4 %, max 30.5 %

Swap used: avg 698 MiB, max 698 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 12.8 | 16.4 |
| 1 | 99.8 | 100.0 |
| 2 | 11.3 | 16.4 |
| 3 | 8.0 | 12.0 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 33.3 %, max 37.0 %

RAM used: avg 5311 MiB, max 5322 MiB, avg 33.5 %, max 33.5 %

Swap used: avg 698 MiB, max 698 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 12.2 | 19.3 |
| 1 | 97.2 | 100.0 |
| 2 | 11.5 | 15.1 |
| 3 | 12.4 | 18.2 |

Decode stage:

CPU total: avg 33.1 %, max 34.8 %

RAM used: avg 5332 MiB, max 5338 MiB, avg 33.6 %, max 33.6 %

Swap used: avg 698 MiB, max 698 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 12.1 | 16.1 |
| 1 | 99.8 | 100.0 |
| 2 | 10.6 | 14.0 |
| 3 | 9.9 | 14.4 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 35.5 %, max 38.3 %

RAM used: avg 5577 MiB, max 5593 MiB, avg 35.1 %, max 35.2 %

Swap used: avg 697 MiB, max 697 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 17.2 | 18.8 |
| 1 | 11.1 | 17.1 |
| 2 | 15.7 | 22.7 |
| 3 | 98.2 | 100.0 |

Decode stage:

CPU total: avg 32.7 %, max 34.4 %

RAM used: avg 5878 MiB, max 5889 MiB, avg 37.0 %, max 37.1 %

Swap used: avg 697 MiB, max 697 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 11.9 | 17.7 |
| 1 | 11.0 | 15.4 |
| 2 | 8.2 | 11.7 |
| 3 | 99.5 | 100.0 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 35.3 %, max 38.4 %

RAM used: avg 6416 MiB, max 6494 MiB, avg 40.4 %, max 40.9 %

Swap used: avg 697 MiB, max 697 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.2 | 100.0 |
| 1 | 13.6 | 27.9 |
| 2 | 15.1 | 19.4 |
| 3 | 12.9 | 21.9 |

Decode stage:

CPU total: avg 33.1 %, max 34.7 %

RAM used: avg 6543 MiB, max 6548 MiB, avg 41.2 %, max 41.2 %

Swap used: avg 697 MiB, max 697 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 87.0 | 100.0 |
| 1 | 20.0 | 68.5 |
| 2 | 11.4 | 15.4 |
| 3 | 14.0 | 30.0 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

No samples in this stage.

Decode stage:

CPU total: avg 34.5 %, max 40.1 %

RAM used: avg 6112 MiB, max 7315 MiB, avg 38.5 %, max 46.1 %

Swap used: avg 696 MiB, max 696 MiB, avg 2.8 %, max 2.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.9 | 100.0 |
| 1 | 12.6 | 24.0 |
| 2 | 12.5 | 22.4 |
| 3 | 12.9 | 26.9 |

