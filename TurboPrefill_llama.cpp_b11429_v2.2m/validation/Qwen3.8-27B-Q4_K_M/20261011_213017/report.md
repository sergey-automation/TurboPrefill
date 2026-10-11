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
- Server PID: `84901`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `PARALLEL=N => exactly N slots and N concurrent requests; request i is pinned to server slot i`
- Metrics policy: `server timings preserved + independent client first-token/wall timings + interval-union aggregate throughput`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/bench_reports_Qwen3.8-27B-Q4_K_M/20261011_213017/llama_server.log`

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
Память:         15Gi       6.2Gi       1.1Gi       1.1Gi       9.6Gi       9.3Gi
Подкачка:       23Gi       616Mi        23Gi
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
0.00.381.151 I srv    load_model: TurboPrefill_llama.cpp_b11429_v2.2m: CUDA Graphs disabled for target and draft contexts
2.31.473.349 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=4096 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=128 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.31.516.363 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=127
2.50.994.786 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=1458175 compute_us=17637127 total_us=19095302
2.51.665.742 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.53.373.598 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=4096 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=128 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
2.53.373.616 I process_ubatch: TurboPrefill recurrent rs_z=-1 first_ubatch=turbo turbo_ubatches=128
3.12.925.656 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=881265 compute_us=18667977 total_us=19549242
3.13.547.062 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.15.530.463 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=625 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=19 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.15.530.476 I process_ubatch: TurboPrefill recurrent rs_z=-1 first_ubatch=turbo turbo_ubatches=19
3.18.772.729 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=127264 compute_us=3112187 total_us=3239451
3.19.140.558 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.36.836.354 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=232 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=7 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.36.836.407 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=6
3.38.427.200 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=399675 compute_us=1047007 total_us=1446682
3.38.763.120 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.53.266.859 I decode: TurboPrefill_llama.cpp_b11429_v2.2m requested=1 active=1 n_tokens=505 n_ubatch=32 real_ubatch=32 n_seq_tokens=32 n_seqs=1 n_seqs_unq=1 equal=1 n_rs_seq=3 turbo_ubatches=15 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.53.266.874 I process_ubatch: TurboPrefill recurrent rs_z=0 first_ubatch=standard turbo_ubatches=14
3.56.031.672 I TurboPrefill_llama.cpp_b11429_v2.2m: accumulation_us=603956 compute_us=2137135 total_us=2741091
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_llama.cpp_b11429_v2.2m/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf --host 0.0.0.0 --port 8081 -lv 4 -ngl 999 -c 17000 --override-kv llama.context_length=int:17000 -b 4096 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer -ts 1/1/1 --flash-attn auto --no-warmup --no-mmproj --spec-type draft-mtp --spec-draft-n-max 3
```

Server PID: `84901`  
Stop command: `kill -INT 84901`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Server prefill tok/s | Server prefill s | Server decode tok/s | Server decode s | Client prefill~ s | Client decode~ s | Client wall s | Group wall s | Group prefill tok/s | Group decode tok/s | Group prefill+decode tok/s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 62.50 | 4.29 | 12.83 | 9.90 | 9.25 | 9.90 | 19.16 | 19.16 | 28.96 | 12.92 | 20.67 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 94.39 | 5.73 | 13.53 | 9.39 | 7.91 | 9.41 | 17.32 | 17.32 | 68.39 | 13.60 | 38.62 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 131.37 | 8.24 | 11.30 | 11.24 | 9.73 | 11.28 | 21.00 | 21.00 | 111.26 | 11.35 | 57.61 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 157.61 | 14.78 | 12.82 | 9.91 | 16.47 | 9.98 | 26.44 | 26.44 | 141.49 | 12.83 | 92.95 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 170.85 | 25.10 | 12.29 | 10.34 | 27.18 | 10.54 | 37.72 | 37.72 | 157.77 | 12.15 | 117.08 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 0.00 | 0.00 | 0.00 | 0.00 | 55.61 | 9.53 | 65.13 | 65.13 | 159.21 | 13.44 | 137.89 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 51.2 | 51.2 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 65.0 | 65.0 | 52.4 | 52.4 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 84.0 | 84.0 | 43.1 | 43.1 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 40.4 | 99.0 | 47.3 | 60.1 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 34.9 | 97.0 | 56.2 | 116.8 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 48.1 | 82.0 | 69.7 | 121.3 | 6459 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 50.0 | 100.0 | 69.6 | 88.1 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 53.0 | 98.0 | 56.3 | 66.2 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 81.0 | 82.0 | 64.3 | 81.2 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 17.2 | 32.0 | 58.3 | 106.8 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 21.5 | 31.0 | 72.5 | 127.8 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 48.8 | 94.0 | 60.3 | 125.5 | 6459 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 47.0 | 100.0 | 49.9 | 64.5 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 65.0 | 98.0 | 56.8 | 83.4 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 70.7 | 89.0 | 80.9 | 104.5 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 14.5 | 32.0 | 58.5 | 81.2 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 30.7 | 44.0 | 68.8 | 116.7 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 47.3 | 67.0 | 68.2 | 119.1 | 6459 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 66.7 | 100.0 | 71.9 | 101.6 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 67.0 | 97.0 | 69.7 | 93.7 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 78.8 | 89.0 | 62.0 | 92.3 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 29.8 | 43.0 | 59.1 | 126.6 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 16.7 | 32.0 | 66.2 | 126.5 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 48.7 | 69.0 | 75.1 | 124.3 | 6459 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 81.8 | 100.0 | 83.5 | 105.8 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 76.5 | 97.0 | 82.3 | 100.1 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 72.2 | 91.0 | 88.1 | 117.1 | 6459 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 21.8 | 34.0 | 61.5 | 122.6 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 28.8 | 64.0 | 57.5 | 104.4 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 50.3 | 69.0 | 81.1 | 118.0 | 6459 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 69.7 | 100.0 | 82.2 | 122.4 | 5563 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 66.1 | 99.0 | 69.7 | 99.8 | 5477 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 76.4 | 100.0 | 74.2 | 104.6 | 6459 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 27.5 %, max 27.5 %

RAM used: avg 4370 MiB, max 4370 MiB, avg 27.5 %, max 27.5 %

Swap used: avg 711 MiB, max 711 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 83.1 | 83.1 |
| 1 | 1.8 | 1.8 |
| 2 | 5.9 | 5.9 |
| 3 | 20.0 | 20.0 |

Decode stage:

CPU total: avg 31.1 %, max 34.4 %

RAM used: avg 4328 MiB, max 4387 MiB, avg 27.3 %, max 27.6 %

Swap used: avg 708 MiB, max 711 MiB, avg 2.9 %, max 2.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 51.9 | 99.5 |
| 1 | 54.5 | 100.0 |
| 2 | 9.6 | 16.3 |
| 3 | 8.3 | 12.1 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 30.1 %, max 32.1 %

RAM used: avg 4389 MiB, max 4525 MiB, avg 27.6 %, max 28.5 %

Swap used: avg 978 MiB, max 983 MiB, avg 4.0 %, max 4.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 15.6 | 17.9 |
| 1 | 16.1 | 23.7 |
| 2 | 70.3 | 90.7 |
| 3 | 17.8 | 21.3 |

Decode stage:

CPU total: avg 32.9 %, max 34.6 %

RAM used: avg 4553 MiB, max 4592 MiB, avg 28.7 %, max 28.9 %

Swap used: avg 951 MiB, max 957 MiB, avg 3.9 %, max 3.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 24.4 | 75.8 |
| 1 | 75.2 | 100.0 |
| 2 | 19.8 | 53.7 |
| 3 | 12.3 | 24.6 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 32.8 %, max 37.8 %

RAM used: avg 4801 MiB, max 4803 MiB, avg 30.2 %, max 30.3 %

Swap used: avg 939 MiB, max 942 MiB, avg 3.8 %, max 3.8 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 12.9 | 19.4 |
| 1 | 94.4 | 100.0 |
| 2 | 12.6 | 19.2 |
| 3 | 11.1 | 15.7 |

Decode stage:

CPU total: avg 32.5 %, max 34.6 %

RAM used: avg 5086 MiB, max 5110 MiB, avg 32.0 %, max 32.2 %

Swap used: avg 917 MiB, max 919 MiB, avg 3.7 %, max 3.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 11.4 | 15.8 |
| 1 | 56.4 | 99.1 |
| 2 | 53.0 | 99.5 |
| 3 | 9.0 | 12.6 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 34.0 %, max 38.4 %

RAM used: avg 5390 MiB, max 5405 MiB, avg 34.0 %, max 34.0 %

Swap used: avg 887 MiB, max 908 MiB, avg 3.6 %, max 3.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 17.1 | 25.1 |
| 1 | 11.7 | 17.3 |
| 2 | 15.3 | 19.0 |
| 3 | 91.8 | 100.0 |

Decode stage:

CPU total: avg 32.4 %, max 34.6 %

RAM used: avg 5709 MiB, max 5736 MiB, avg 36.0 %, max 36.1 %

Swap used: avg 843 MiB, max 848 MiB, avg 3.4 %, max 3.4 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 98.5 | 100.0 |
| 1 | 11.7 | 17.2 |
| 2 | 9.5 | 14.8 |
| 3 | 9.6 | 13.0 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 34.2 %, max 38.2 %

RAM used: avg 6102 MiB, max 6151 MiB, avg 38.4 %, max 38.7 %

Swap used: avg 795 MiB, max 835 MiB, avg 3.2 %, max 3.4 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 16.7 | 31.5 |
| 1 | 13.1 | 19.1 |
| 2 | 19.1 | 89.2 |
| 3 | 87.8 | 100.0 |

Decode stage:

CPU total: avg 33.1 %, max 34.3 %

RAM used: avg 6449 MiB, max 6479 MiB, avg 40.6 %, max 40.8 %

Swap used: avg 759 MiB, max 759 MiB, avg 3.1 %, max 3.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 58.3 | 100.0 |
| 1 | 22.5 | 80.5 |
| 2 | 42.1 | 100.0 |
| 3 | 9.5 | 12.6 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

No samples in this stage.

Decode stage:

CPU total: avg 34.3 %, max 38.5 %

RAM used: avg 6128 MiB, max 7296 MiB, avg 38.6 %, max 46.0 %

Swap used: avg 725 MiB, max 758 MiB, avg 3.0 %, max 3.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 14.0 | 26.0 |
| 1 | 10.9 | 17.5 |
| 2 | 60.5 | 100.0 |
| 3 | 51.5 | 100.0 |

