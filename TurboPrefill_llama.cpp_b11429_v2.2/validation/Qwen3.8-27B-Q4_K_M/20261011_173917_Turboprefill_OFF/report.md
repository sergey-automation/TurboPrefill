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
- TurboPrefill version: `TurboPrefill_b11429_v2.2`
- llama.cpp git describe: `v0.6.0-dirty`
- llama.cpp git commit: `d81235049384534c167caea52b85a694f6103d14`
- Server PID: `67278`
- KEEP_SERVER_RUNNING: `1`
- Parallel-slots mode: `PARALLEL=N => exactly N slots and N concurrent requests; request i is pinned to server slot i`
- Metrics policy: `server timings preserved + independent client first-token/wall timings + interval-union aggregate throughput`
- llama_server_log: `/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/bench_reports_Qwen3.8-27B-Q4_K_M/20261011_173917/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
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
CPU(s) scaling MHz:                      89%
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
Подкачка:       23Gi       576Mi        23Gi
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
2.41.015.705 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.26.075.975 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
3.27.795.562 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.15.310.079 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.17.306.414 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.24.919.207 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=625 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.41.971.989 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.44.549.221 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=232 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
4.58.015.680 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=505 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.03.206.480 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=505 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.16.656.660 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=1046 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.27.659.091 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=1046 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
5.43.175.800 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=2294 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
6.07.681.368 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=2294 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
6.24.828.757 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
7.10.686.137 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
7.12.438.776 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=156 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
7.14.142.664 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=156 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
7.34.070.160 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=3 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
8.18.763.635 I decode: TurboPrefill_b11429_v2.2 requested=0 active=0 n_tokens=4096 n_ubatch=32 real_ubatch=0 n_seq_tokens=0 n_seqs=0 n_seqs_unq=0 equal=0 n_rs_seq=0 turbo_ubatches=0 devices=3 pipeline=1 split_mode=1 embeddings_nextn=1
```

## Server command

```bash
/home/serg/workspace/versions/TurboPrefill_b11429_v2.2/build/bin/llama-server -m /mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf --host 0.0.0.0 --port 8081 -lv 4 -ngl 999 -c 17000 --override-kv llama.context_length=int:17000 -b 4096 -ub 32 -np 1 -ctk f16 -ctv f16 -sm layer -ts 1/1/1 --flash-attn auto --no-warmup --no-mmproj --spec-type draft-mtp --spec-draft-n-max 3
```

Server PID: `67278`  
Stop command: `kill -INT 67278`

## Summary

| File | Active slots | Request | Prompt tokens | Completion tokens | Server prefill tok/s | Server prefill s | Server decode tok/s | Server decode s | Client prefill~ s | Client decode~ s | Client wall s | Group wall s | Group prefill tok/s | Group decode tok/s | Group prefill+decode tok/s |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ctx_000256.txt | 1 | 1 | 268 | 128 | 54.63 | 4.91 | 12.83 | 9.90 | 9.27 | 9.91 | 19.19 | 19.19 | 28.90 | 12.91 | 20.64 |
| ctx_000512.txt | 1 | 1 | 541 | 128 | 70.92 | 7.63 | 13.44 | 9.45 | 8.83 | 9.46 | 18.29 | 18.29 | 61.26 | 13.53 | 36.58 |
| ctx_001024.txt | 1 | 1 | 1082 | 128 | 79.04 | 13.69 | 11.35 | 11.18 | 15.22 | 11.21 | 26.44 | 26.44 | 71.08 | 11.41 | 45.77 |
| ctx_002048.txt | 1 | 1 | 2330 | 128 | 83.96 | 27.75 | 12.27 | 10.35 | 29.37 | 10.55 | 39.92 | 39.92 | 79.33 | 12.13 | 61.57 |
| ctx_004096.txt | 1 | 1 | 4288 | 128 | 82.70 | 51.85 | 12.26 | 10.36 | 55.10 | 10.54 | 65.64 | 65.64 | 77.83 | 12.15 | 67.28 |
| ctx_008192.txt | 1 | 1 | 8853 | 128 | 0.00 | 0.00 | 0.00 | 0.00 | 113.36 | 13.03 | 126.39 | 126.39 | 78.09 | 9.83 | 71.06 |

## GPU load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 58.0 | 100.0 | 78.4 | 105.4 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 0.0 | 0.0 | 52.5 | 52.6 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 21.0 | 42.0 | 51.4 | 51.6 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 32.2 | 83.0 | 44.0 | 51.4 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 38.8 | 89.0 | 51.6 | 93.6 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 34.2 | 63.0 | 71.9 | 98.0 | 6457 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 18.3 | 29.0 | 63.1 | 103.0 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 25.7 | 69.0 | 64.0 | 106.9 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 55.7 | 95.0 | 43.1 | 45.9 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 18.0 | 32.0 | 66.5 | 115.9 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 20.6 | 31.0 | 84.2 | 122.2 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 60.4 | 67.0 | 71.7 | 118.9 | 6457 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 58.2 | 99.0 | 64.7 | 111.6 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 22.5 | 44.0 | 68.5 | 97.1 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 21.0 | 39.0 | 51.5 | 96.4 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 17.6 | 32.0 | 88.9 | 126.6 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 25.4 | 31.0 | 91.7 | 133.7 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 55.4 | 68.0 | 42.4 | 44.8 | 6457 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 29.3 | 78.0 | 57.6 | 89.2 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 27.7 | 74.0 | 59.7 | 105.1 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 48.1 | 98.0 | 58.6 | 97.3 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 32.2 | 92.0 | 47.6 | 59.6 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 17.5 | 32.0 | 68.5 | 121.6 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 35.7 | 68.0 | 53.5 | 80.4 | 6457 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 36.0 | 82.0 | 60.7 | 109.5 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 32.2 | 99.0 | 59.4 | 105.2 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 35.7 | 98.0 | 61.3 | 111.1 | 6457 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 34.8 | 73.0 | 57.9 | 128.9 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 15.3 | 33.0 | 47.0 | 61.5 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 49.2 | 70.0 | 78.1 | 128.6 | 6457 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA P104-100 | Gen1 x1 | 30.3 | 100.0 | 67.9 | 117.8 | 5561 |
| 1 | NVIDIA P104-100 | Gen1 x1 | 32.9 | 98.0 | 59.8 | 126.8 | 5475 |
| 2 | NVIDIA P104-100 | Gen1 x1 | 44.5 | 91.0 | 57.7 | 138.7 | 6457 |


## CPU / RAM / swap load by stage

### ctx_000256.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 60.2 %, max 60.8 %

RAM used: avg 7387 MiB, max 7400 MiB, avg 46.5 %, max 46.6 %

Swap used: avg 921 MiB, max 921 MiB, avg 3.7 %, max 3.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 17.5 | 18.8 |
| 1 | 23.9 | 25.5 |
| 2 | 99.8 | 100.0 |
| 3 | 99.5 | 100.0 |

Decode stage:

CPU total: avg 65.3 %, max 70.8 %

RAM used: avg 7684 MiB, max 7839 MiB, avg 48.4 %, max 49.4 %

Swap used: avg 921 MiB, max 921 MiB, avg 3.7 %, max 3.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 70.9 | 100.0 |
| 1 | 45.3 | 94.8 |
| 2 | 67.2 | 97.3 |
| 3 | 77.2 | 100.0 |

### ctx_000512.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 64.5 %, max 65.6 %

RAM used: avg 8002 MiB, max 8006 MiB, avg 50.4 %, max 50.4 %

Swap used: avg 921 MiB, max 921 MiB, avg 3.7 %, max 3.7 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 55.3 | 94.5 |
| 1 | 77.8 | 100.0 |
| 2 | 72.6 | 95.9 |
| 3 | 52.2 | 90.9 |

Decode stage:

CPU total: avg 65.8 %, max 70.8 %

RAM used: avg 8516 MiB, max 8639 MiB, avg 53.6 %, max 54.4 %

Swap used: avg 938 MiB, max 950 MiB, avg 3.8 %, max 3.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 57.5 | 92.3 |
| 1 | 92.1 | 99.5 |
| 2 | 53.4 | 92.1 |
| 3 | 60.1 | 96.9 |

### ctx_001024.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 65.0 %, max 68.3 %

RAM used: avg 9146 MiB, max 9272 MiB, avg 57.6 %, max 58.4 %

Swap used: avg 950 MiB, max 950 MiB, avg 3.9 %, max 3.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 100.0 | 100.0 |
| 1 | 56.2 | 100.0 |
| 2 | 46.1 | 96.4 |
| 3 | 57.5 | 100.0 |

Decode stage:

CPU total: avg 66.1 %, max 68.6 %

RAM used: avg 9559 MiB, max 10017 MiB, avg 60.2 %, max 63.1 %

Swap used: avg 950 MiB, max 950 MiB, avg 3.9 %, max 3.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 76.7 | 99.1 |
| 1 | 63.3 | 96.4 |
| 2 | 51.5 | 69.5 |
| 3 | 72.8 | 100.0 |

### ctx_002048.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 66.0 %, max 69.1 %

RAM used: avg 10166 MiB, max 10313 MiB, avg 64.0 %, max 65.0 %

Swap used: avg 949 MiB, max 949 MiB, avg 3.9 %, max 3.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 54.6 | 100.0 |
| 1 | 68.5 | 100.0 |
| 2 | 72.8 | 100.0 |
| 3 | 67.8 | 100.0 |

Decode stage:

CPU total: avg 65.5 %, max 67.2 %

RAM used: avg 10574 MiB, max 10607 MiB, avg 66.6 %, max 66.8 %

Swap used: avg 960 MiB, max 1017 MiB, avg 3.9 %, max 4.1 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 74.3 | 100.0 |
| 1 | 64.6 | 100.0 |
| 2 | 65.0 | 99.5 |
| 3 | 57.9 | 100.0 |

### ctx_004096.txt | active_slots=1 | request=1

Prefill stage:

CPU total: avg 61.2 %, max 69.6 %

RAM used: avg 10238 MiB, max 11694 MiB, avg 64.5 %, max 73.7 %

Swap used: avg 1162 MiB, max 1452 MiB, avg 4.7 %, max 5.9 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 79.7 | 100.0 |
| 1 | 69.5 | 100.0 |
| 2 | 50.2 | 100.0 |
| 3 | 45.1 | 95.3 |

Decode stage:

CPU total: avg 67.5 %, max 71.6 %

RAM used: avg 10602 MiB, max 10739 MiB, avg 66.8 %, max 67.7 %

Swap used: avg 994 MiB, max 994 MiB, avg 4.0 %, max 4.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 55.7 | 98.7 |
| 1 | 81.5 | 100.0 |
| 2 | 49.2 | 96.9 |
| 3 | 83.5 | 100.0 |

### ctx_008192.txt | active_slots=1 | request=1

Prefill stage:

No samples in this stage.

Decode stage:

CPU total: avg 40.2 %, max 67.1 %

RAM used: avg 6048 MiB, max 11674 MiB, avg 38.1 %, max 73.5 %

Swap used: avg 776 MiB, max 993 MiB, avg 3.2 %, max 4.0 %

| Logical CPU | avg util % | max util % |
|---:|---:|---:|
| 0 | 94.7 | 100.0 |
| 1 | 21.3 | 100.0 |
| 2 | 25.2 | 100.0 |
| 3 | 19.4 | 100.0 |

