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
- TurboPrefill version: `TurboPrefill_b11429_v2.2:`
- llama.cpp git describe: `v0.6.0-dirty`
- llama.cpp git commit: `d81235049384534c167caea52b85a694f6103d14`
- Server PID: `67106`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `PARALLEL=N => exactly N slots and N concurrent requests; request i is pinned to server slot i`
- Metrics policy: `server timings preserved + independent client first-token/wall timings + interval-union aggregate throughput`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/bench_reports_Qwen3.8-27B-Q4_K_M/20261011_172915/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
```

### RUN_DIR

```text
/home/serg/workspace/versions/TurboPrefill_b11429_v2.2
```

### CONFIG_PATH

```text
/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/config_Qwen_3.8.sh
```

### LLAMA_SERVER_BIN

```text
/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/build/bin/llama-server
```

### LOCAL_LD_LIBRARY_PATH

```text
/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/build/bin
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
CPU(s) scaling MHz:                      97%
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
Память:         15Gi       913Mi       551Mi        40Mi        14Gi        14Gi
Подкачка:       23Gi       418Mi        23Gi
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
0.00.466.273 I srv    load_model: TurboPrefill_b11429_v2.2: CUDA Graphs disabled for target and draft contexts
2.30.471.437 I decode: TurboPrefill_b11429_v2.2 requested=1 active=1 n_tokens=4096 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=128 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.30.521.850 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=127
2.49.995.988 I TurboPrefill_b11429_v2.2: accumulation_us=1440460 compute_us=17644363 total_us=19084823
2.50.662.754 I decode: TurboPrefill_b11429_v2.2 requested=1 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.52.381.186 I decode: TurboPrefill_b11429_v2.2 requested=1 active=1 n_tokens=4096 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=128 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.52.381.204 I process_ubatch: TurboPrefill recurrent rs_z=-1 first_ubatch=turbo turbo_ubatches=128
3.11.869.725 I TurboPrefill_b11429_v2.2: accumulation_us=853650 compute_us=18631944 total_us=19485594
3.12.502.585 I decode: TurboPrefill_b11429_v2.2 requested=1 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.14.494.960 I decode: TurboPrefill_b11429_v2.2 requested=1 active=1 n_tokens=625 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=19 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.14.494.975 I process_ubatch: TurboPrefill recurrent rs_z=-1 first_ubatch=turbo turbo_ubatches=19
3.17.736.806 I TurboPrefill_b11429_v2.2: accumulation_us=122791 compute_us=3116257 total_us=3239048
3.18.107.894 I decode: TurboPrefill_b11429_v2.2 requested=1 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.35.103.589 I decode: TurboPrefill_b11429_v2.2 requested=1 active=1 n_tokens=232 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=7 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.35.103.603 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=6
3.36.560.527 I TurboPrefill_b11429_v2.2: accumulation_us=391271 compute_us=1044406 total_us=1435677
3.36.885.839 I decode: TurboPrefill_b11429_v2.2 requested=1 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.50.272.404 I decode: TurboPrefill_b11429_v2.2 requested=1 active=1 n_tokens=505 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=15 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.50.272.416 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=14
3.52.834.174 I TurboPrefill_b11429_v2.2: accumulation_us=431588 compute_us=2109162 total_us=2540750
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf --host 0.0.0.0 --port 8081 -lv 4 -ngl 999 -c 17000 --override-kv llama.context_length=int:17000 -b 4096 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer -ts 1/1/1 --flash-attn auto --no-warmup --no-mmproj --spec-type draft-mtp --spec-draft-n-max 3
```

Server PID: `67106`  
Stop command: `kill -INT 67106`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Server prefill tok/s | Server prefill s | Server decode tok/s | Server decode s | Client prefill~ s | Client decode~ s | Client wall s | Group wall s | Group prefill tok/s | Group decode tok/s | Group prefill+decode tok/s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 65.20 | 4.11 | 12.85 | 9.88 | 8.43 | 9.89 | 18.32 | 18.32 | 31.80 | 12.94 | 21.62 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 101.02 | 5.36 | 13.49 | 9.41 | 6.50 | 9.43 | 15.93 | 15.93 | 83.18 | 13.58 | 41.99 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 136.19 | 7.94 | 11.41 | 11.13 | 9.21 | 11.16 | 20.37 | 20.37 | 117.50 | 11.47 | 59.41 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 165.49 | 14.08 | 12.84 | 9.89 | 15.56 | 9.94 | 25.50 | 25.50 | 149.77 | 12.87 | 96.39 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 177.03 | 24.22 | 12.32 | 10.31 | 26.14 | 10.49 | 36.63 | 36.63 | 164.03 | 12.21 | 120.56 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 0.00 | 0.00 | 0.00 | 0.00 | 55.39 | 9.50 | 64.89 | 64.89 | 159.84 | 13.47 | 138.41 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 100.0 | 100.0 | 51.4 | 51.4 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 51.5 | 51.5 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 50.7 | 50.7 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 22.7 | 36.0 | 47.7 | 60.6 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 8.7 | 28.0 | 62.1 | 118.6 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 44.0 | 99.0 | 73.1 | 124.4 | 6459 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 50.0 | 100.0 | 75.0 | 104.4 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 48.5 | 97.0 | 69.6 | 96.7 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 78.5 | 88.0 | 72.1 | 94.9 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 26.0 | 32.0 | 57.6 | 121.9 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 12.4 | 22.0 | 61.7 | 106.3 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 40.6 | 53.0 | 79.3 | 115.7 | 6459 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 85.7 | 100.0 | 72.6 | 90.2 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 75.7 | 95.0 | 73.0 | 91.9 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 39.3 | 88.0 | 88.9 | 102.7 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 30.8 | 73.0 | 55.2 | 90.1 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 28.2 | 31.0 | 56.7 | 86.3 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 46.8 | 68.0 | 62.6 | 91.7 | 6459 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 66.7 | 100.0 | 78.6 | 105.2 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 63.8 | 97.0 | 77.2 | 100.3 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 80.5 | 98.0 | 89.3 | 104.9 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 17.6 | 33.0 | 73.9 | 120.1 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 38.8 | 87.0 | 46.7 | 55.1 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 36.2 | 69.0 | 72.9 | 120.8 | 6459 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 79.8 | 100.0 | 77.4 | 100.8 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 70.2 | 98.0 | 79.2 | 96.5 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 79.0 | 98.0 | 80.8 | 108.6 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 21.8 | 34.0 | 70.3 | 125.2 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 20.8 | 33.0 | 52.3 | 91.0 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 57.0 | 95.0 | 55.9 | 91.3 | 6459 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 68.1 | 100.0 | 71.7 | 104.8 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 65.0 | 99.0 | 74.9 | 101.6 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 74.5 | 98.0 | 76.4 | 114.3 | 6459 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 26.1 %, max 26.1 %

RAM used: avg 4469 MiB, max 4469 MiB, avg 28.1 %, max 28.1 %

Swap used: avg 663 MiB, max 663 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 3.3 | 3.3 |
| 1 | 0.9 | 0.9 |
| 2 | 1.4 | 1.4 |
| 3 | 99.1 | 99.1 |

Decode stage:

CPU total: avg 32.0 %, max 34.5 %

RAM used: avg 4393 MiB, max 4469 MiB, avg 27.7 %, max 28.1 %

Swap used: avg 662 MiB, max 663 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 50.8 | 100.0 |
| 1 | 7.8 | 13.1 |
| 2 | 11.0 | 18.7 |
| 3 | 58.1 | 100.0 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 32.1 %, max 35.2 %

RAM used: avg 4867 MiB, max 4868 MiB, avg 30.7 %, max 30.7 %

Swap used: avg 662 MiB, max 662 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 8.2 | 11.2 |
| 1 | 10.1 | 14.0 |
| 2 | 10.0 | 15.3 |
| 3 | 99.5 | 100.0 |

Decode stage:

CPU total: avg 33.4 %, max 34.3 %

RAM used: avg 4896 MiB, max 4913 MiB, avg 30.8 %, max 30.9 %

Swap used: avg 662 MiB, max 662 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 9.4 | 11.7 |
| 1 | 61.2 | 100.0 |
| 2 | 12.0 | 16.0 |
| 3 | 51.0 | 100.0 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 34.6 %, max 38.2 %

RAM used: avg 5370 MiB, max 5382 MiB, avg 33.8 %, max 33.9 %

Swap used: avg 662 MiB, max 662 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 12.5 | 17.0 |
| 1 | 99.4 | 100.0 |
| 2 | 12.6 | 18.0 |
| 3 | 13.8 | 17.5 |

Decode stage:

CPU total: avg 33.0 %, max 34.4 %

RAM used: avg 5385 MiB, max 5388 MiB, avg 33.9 %, max 33.9 %

Swap used: avg 662 MiB, max 662 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 10.9 | 12.6 |
| 1 | 54.8 | 100.0 |
| 2 | 10.0 | 14.0 |
| 3 | 56.4 | 100.0 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 35.1 %, max 38.1 %

RAM used: avg 5877 MiB, max 5904 MiB, avg 37.0 %, max 37.2 %

Swap used: avg 662 MiB, max 662 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 13.8 | 20.8 |
| 1 | 13.2 | 19.0 |
| 2 | 13.9 | 18.5 |
| 3 | 99.6 | 100.0 |

Decode stage:

CPU total: avg 32.7 %, max 34.4 %

RAM used: avg 5925 MiB, max 5927 MiB, avg 37.3 %, max 37.3 %

Swap used: avg 662 MiB, max 662 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 10.2 | 12.7 |
| 1 | 9.6 | 13.6 |
| 2 | 84.4 | 100.0 |
| 3 | 26.3 | 81.8 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 35.3 %, max 38.6 %

RAM used: avg 6460 MiB, max 6543 MiB, avg 40.7 %, max 41.2 %

Swap used: avg 661 MiB, max 661 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 14.1 | 19.0 |
| 1 | 12.5 | 19.1 |
| 2 | 99.9 | 100.0 |
| 3 | 14.5 | 27.4 |

Decode stage:

CPU total: avg 32.9 %, max 34.3 %

RAM used: avg 6581 MiB, max 6594 MiB, avg 41.5 %, max 41.5 %

Swap used: avg 661 MiB, max 661 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 12.8 | 18.0 |
| 1 | 10.5 | 12.7 |
| 2 | 99.3 | 100.0 |
| 3 | 9.0 | 10.8 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

No samples in this stage.

Decode stage:

CPU total: avg 34.3 %, max 38.5 %

RAM used: avg 6188 MiB, max 7365 MiB, avg 39.0 %, max 46.4 %

Swap used: avg 660 MiB, max 661 MiB, avg 2.7 %, max 2.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 13.5 | 27.5 |
| 1 | 12.1 | 19.1 |
| 2 | 99.9 | 100.0 |
| 3 | 11.7 | 18.4 |

