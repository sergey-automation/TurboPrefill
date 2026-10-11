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
- TURBOPREFILL: `0`
- TurboPrefill status: `TurboPrefill implementation detected; inactive (TURBOPREFILL=0)`
- TurboPrefill version: `TurboPrefill_llama.cpp_b11429_v2.2m`
- llama.cpp git describe: `v0.6.0-dirty`
- llama.cpp git commit: `d81235049384534c167caea52b85a694f6103d14`
- Server PID: `85073`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `PARALLEL=N => exactly N slots and N concurrent requests; request i is pinned to server slot i`
- Metrics policy: `server timings preserved + independent client first-token/wall timings + interval-union aggregate throughput`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/bench_reports_Qwen3.8-27B-Q4_K_M/20261011_214030/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
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
CPU(s) scaling MHz:                      22%
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
Память:         15Gi       6.2Gi       1.1Gi       1.1Gi       9.6Gi       9.3Gi
Подкачка:       23Gi       636Mi        23Gi
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
2.22.650.214 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.07.935.089 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.09.653.343 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.57.158.632 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.59.142.245 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.06.745.085 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.24.027.628 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.26.689.101 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.40.309.630 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=505 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.45.551.799 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=505 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.58.824.761 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=1046 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.09.876.576 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=1046 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.25.332.969 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=2294 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.49.916.000 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=2294 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
6.05.166.747 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
6.49.886.145 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
6.51.548.711 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=156 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
6.53.249.255 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=156 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
7.13.019.168 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
7.57.659.192 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf --host 0.0.0.0 --port 8081 -lv 4 -ngl 999 -c 17000 --override-kv llama.context_length=int:17000 -b 4096 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer -ts 1/1/1 --flash-attn auto --no-warmup --no-mmproj --spec-type draft-mtp --spec-draft-n-max 3
```

Server PID: `85073`  
Stop command: `kill -INT 85073`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Server prefill tok/s | Server prefill s | Server decode tok/s | Server decode s | Client prefill~ s | Client decode~ s | Client wall s | Group wall s | Group prefill tok/s | Group decode tok/s | Group prefill+decode tok/s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 53.29 | 5.03 | 12.83 | 9.90 | 9.59 | 9.90 | 19.49 | 19.49 | 27.95 | 12.92 | 20.32 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 70.43 | 7.68 | 13.50 | 9.41 | 8.97 | 9.42 | 18.40 | 18.40 | 60.30 | 13.58 | 36.37 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 78.88 | 13.72 | 11.40 | 11.14 | 15.13 | 11.17 | 26.30 | 26.30 | 71.53 | 11.46 | 46.01 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 83.79 | 27.81 | 12.82 | 9.91 | 29.42 | 9.96 | 39.38 | 39.38 | 79.21 | 12.85 | 62.42 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 84.75 | 50.59 | 12.32 | 10.31 | 52.64 | 10.49 | 63.13 | 63.13 | 81.46 | 12.20 | 69.95 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 0.00 | 0.00 | 0.00 | 0.00 | 113.22 | 9.50 | 122.72 | 122.72 | 78.19 | 13.47 | 73.18 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 51.3 | 51.5 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 24.5 | 49.0 | 51.9 | 51.9 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 98.0 | 99.0 | 50.7 | 50.9 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 24.7 | 54.0 | 63.7 | 118.0 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 16.7 | 31.0 | 53.9 | 87.0 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 57.6 | 75.0 | 66.2 | 121.0 | 6457 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 23.7 | 41.0 | 59.3 | 92.0 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 52.7 | 85.0 | 63.5 | 105.3 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 43.3 | 82.0 | 59.4 | 91.5 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 21.0 | 32.0 | 60.9 | 106.1 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 30.2 | 67.0 | 62.7 | 120.4 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 57.2 | 68.0 | 63.8 | 123.2 | 6457 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 34.7 | 77.0 | 60.6 | 101.5 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 30.5 | 64.0 | 47.8 | 63.3 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 48.0 | 98.0 | 70.7 | 127.5 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 19.2 | 32.0 | 58.8 | 121.0 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 19.2 | 31.0 | 64.6 | 146.9 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 57.8 | 68.0 | 77.4 | 128.8 | 6457 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 33.8 | 98.0 | 63.7 | 109.8 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 39.7 | 90.0 | 66.5 | 133.1 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 39.6 | 76.0 | 55.7 | 99.2 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 28.0 | 33.0 | 57.5 | 118.1 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 24.8 | 31.0 | 65.0 | 130.4 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 54.8 | 66.0 | 85.0 | 124.2 | 6457 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 39.1 | 96.0 | 67.1 | 154.7 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 34.8 | 99.0 | 60.9 | 122.9 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 39.5 | 98.0 | 61.2 | 129.9 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 32.0 | 61.0 | 54.2 | 114.9 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 17.8 | 33.0 | 57.9 | 94.4 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 46.2 | 69.0 | 80.5 | 126.7 | 6457 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 42.4 | 98.0 | 59.5 | 124.6 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 32.7 | 99.0 | 68.6 | 108.0 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 35.7 | 99.0 | 59.9 | 131.1 | 6457 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 27.5 %, max 29.2 %

RAM used: avg 3246 MiB, max 3255 MiB, avg 20.4 %, max 20.5 %

Swap used: avg 713 MiB, max 713 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 98.1 | 100.0 |
| 1 | 0.9 | 1.9 |
| 2 | 9.6 | 16.4 |
| 3 | 1.6 | 2.3 |

Decode stage:

CPU total: avg 32.6 %, max 34.4 %

RAM used: avg 3200 MiB, max 3226 MiB, avg 20.2 %, max 20.3 %

Swap used: avg 726 MiB, max 733 MiB, avg 3.0 %, max 3.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 98.5 | 100.0 |
| 1 | 11.9 | 16.5 |
| 2 | 9.8 | 12.7 |
| 3 | 10.1 | 11.7 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 30.3 %, max 31.9 %

RAM used: avg 3691 MiB, max 3709 MiB, avg 23.3 %, max 23.4 %

Swap used: avg 732 MiB, max 732 MiB, avg 3.0 %, max 3.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 96.9 | 99.1 |
| 1 | 8.4 | 11.6 |
| 2 | 7.1 | 8.9 |
| 3 | 8.6 | 9.8 |

Decode stage:

CPU total: avg 32.9 %, max 34.5 %

RAM used: avg 3697 MiB, max 3704 MiB, avg 23.3 %, max 23.3 %

Swap used: avg 728 MiB, max 729 MiB, avg 3.0 %, max 3.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.7 | 100.0 |
| 1 | 10.8 | 14.4 |
| 2 | 12.1 | 17.2 |
| 3 | 9.1 | 12.6 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 31.1 %, max 32.2 %

RAM used: avg 4139 MiB, max 4185 MiB, avg 26.1 %, max 26.4 %

Swap used: avg 726 MiB, max 726 MiB, avg 3.0 %, max 3.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 50.3 | 99.5 |
| 1 | 9.8 | 11.7 |
| 2 | 56.5 | 99.5 |
| 3 | 8.0 | 11.3 |

Decode stage:

CPU total: avg 33.5 %, max 34.8 %

RAM used: avg 4308 MiB, max 4359 MiB, avg 27.1 %, max 27.5 %

Swap used: avg 723 MiB, max 725 MiB, avg 2.9 %, max 3.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 87.6 | 100.0 |
| 1 | 23.6 | 85.6 |
| 2 | 11.1 | 15.0 |
| 3 | 11.4 | 15.3 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 31.2 %, max 32.1 %

RAM used: avg 4656 MiB, max 4744 MiB, avg 29.3 %, max 29.9 %

Swap used: avg 722 MiB, max 723 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 49.1 | 100.0 |
| 1 | 16.9 | 99.5 |
| 2 | 9.0 | 11.7 |
| 3 | 49.7 | 99.5 |

Decode stage:

CPU total: avg 33.5 %, max 34.6 %

RAM used: avg 4779 MiB, max 4817 MiB, avg 30.1 %, max 30.3 %

Swap used: avg 722 MiB, max 722 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 100.0 | 100.0 |
| 1 | 11.3 | 14.4 |
| 2 | 12.0 | 16.7 |
| 3 | 10.6 | 12.2 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 31.5 %, max 32.3 %

RAM used: avg 5184 MiB, max 5353 MiB, avg 32.7 %, max 33.7 %

Swap used: avg 721 MiB, max 721 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.4 | 100.0 |
| 1 | 8.9 | 11.8 |
| 2 | 9.1 | 12.3 |
| 3 | 8.5 | 12.6 |

Decode stage:

CPU total: avg 32.9 %, max 34.6 %

RAM used: avg 5358 MiB, max 5392 MiB, avg 33.7 %, max 34.0 %

Swap used: avg 721 MiB, max 721 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 99.9 | 100.0 |
| 1 | 11.1 | 15.4 |
| 2 | 11.0 | 15.3 |
| 3 | 9.4 | 12.2 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

No samples in this stage.

Decode stage:

CPU total: avg 31.5 %, max 34.3 %

RAM used: avg 4900 MiB, max 6170 MiB, avg 30.9 %, max 38.9 %

Swap used: avg 720 MiB, max 721 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 16.6 | 100.0 |
| 1 | 8.6 | 15.0 |
| 2 | 92.7 | 100.0 |
| 3 | 8.1 | 12.4 |

