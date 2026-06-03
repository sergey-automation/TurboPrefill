# llama-server context benchmark report

## Test header

- MODEL: `/workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf`
- NGL: `99`
- CTX_SIZE: `66032`
- N_GEN: `128`
- BATCH: `16384`
- UBATCH: `768`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1/1`
- PARALLEL: `2`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/workspace/bench_reports_gpt-120b_5xRTX5060ti/20260602_145406/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
```

### nvidia_smi

```text
0, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
1, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
2, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
3, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
4, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
5, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
6, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
7, NVIDIA GeForce RTX 5060 Ti, 580.159.03, 16311 MiB
```

### nvcc

```text
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2025 NVIDIA Corporation
Built on Wed_Aug_20_01:58:59_PM_PDT_2025
Cuda compilation tools, release 13.0, V13.0.88
Build cuda_13.0.r13.0/compiler.36424714_0
```

### cmake

```text
cmake version 3.28.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Server command

```bash
./build/bin/llama-server -m /workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66032 -b 16384 -ub 768 -np 2 -ctk f16 -sm layer -ts 1/1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 2784 | 128 | 2028.67 | 1.37 | 96.87 | 2.72 |
| ctx_002_000512.txt | 255 | 128 | 1076.09 | 0.24 | 100.45 | 1.52 |
| ctx_003_001024.txt | 504 | 128 | 1621.26 | 0.31 | 99.87 | 1.63 |
| ctx_004_002048.txt | 1017 | 128 | 1777.73 | 0.57 | 98.85 | 1.93 |
| ctx_005_004096.txt | 2044 | 128 | 2047.53 | 1.00 | 97.80 | 2.48 |
| ctx_006_006144.txt | 4076 | 128 | 3049.46 | 1.34 | 95.57 | 2.82 |
| ctx_007_008192.txt | 6142 | 128 | 3416.35 | 1.80 | 93.24 | 3.37 |
| ctx_008_012288.txt | 8164 | 128 | 3809.92 | 2.14 | 93.16 | 3.77 |
| ctx_009_016384.txt | 12280 | 127 | 3899.09 | 3.15 | 90.28 | 4.86 |
| ctx_010_024576.txt | 16373 | 128 | 3886.47 | 4.21 | 87.36 | 6.08 |
| ctx_011_032768.txt | 24560 | 128 | 3345.63 | 7.34 | 82.14 | 9.45 |
| ctx_012_065536.txt | 32761 | 128 | 3109.79 | 10.53 | 77.47 | 12.83 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 32.0 | 46.6 | 55.6 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.7 | 43.0 | 44.4 | 48.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.7 | 67.0 | 44.4 | 49.9 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.0 | 57.0 | 41.0 | 48.1 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.3 | 34.0 | 38.2 | 42.6 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 19.2 | 22.0 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 22.0 | 25.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen2 x8 | 0.0 | 0.0 | 21.4 | 24.4 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 18.0 | 49.4 | 50.5 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 16.0 | 51.8 | 51.9 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.5 | 18.0 | 56.6 | 58.6 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.5 | 16.0 | 50.8 | 53.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.0 | 27.0 | 60.2 | 62.7 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 13.4 | 13.7 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 13.3 | 15.2 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 13.9 | 15.4 | 142 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 29.0 | 53.0 | 47.1 | 49.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 16.0 | 45.2 | 47.9 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 18.0 | 45.8 | 49.5 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 16.0 | 44.6 | 50.1 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.7 | 28.0 | 52.4 | 59.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 11.5 | 12.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 10.2 | 10.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 10.6 | 11.3 | 142 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 43.9 | 43.9 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 9.0 | 36.8 | 36.8 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.6 | 35.6 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.3 | 36.3 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 43.1 | 43.1 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.0 | 17.0 | 45.1 | 50.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 16.0 | 45.6 | 50.5 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 18.0 | 45.0 | 50.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.5 | 16.0 | 44.1 | 48.3 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 28.5 | 29.0 | 48.0 | 55.8 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.0 | 9.2 | 142 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 41.1 | 41.1 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 40.1 | 40.1 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 42.0 | 42.0 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.7 | 37.7 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 43.7 | 43.7 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 18.0 | 47.9 | 52.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 16.0 | 45.6 | 48.2 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 18.0 | 47.5 | 52.4 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.7 | 16.0 | 45.7 | 50.9 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.0 | 28.0 | 50.2 | 62.5 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.7 | 142 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 2.5 | 5.0 | 49.8 | 50.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 3.0 | 6.0 | 46.7 | 47.4 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 2.0 | 46.6 | 47.9 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 43.4 | 44.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 28.0 | 47.0 | 50.1 | 56.6 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.3 | 43.0 | 51.3 | 56.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.3 | 16.0 | 48.9 | 50.5 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 29.7 | 53.0 | 50.9 | 51.5 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 15.0 | 48.1 | 53.1 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.3 | 28.0 | 48.4 | 60.4 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.6 | 142 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 28.7 | 86.0 | 60.3 | 77.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.0 | 63.0 | 52.5 | 64.1 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.0 | 66.0 | 49.9 | 64.9 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 30.3 | 62.0 | 45.8 | 60.1 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.7 | 45.0 | 42.8 | 50.5 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.7 | 18.0 | 56.0 | 62.1 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.3 | 17.0 | 53.8 | 57.5 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.3 | 19.0 | 59.5 | 71.5 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 17.0 | 56.8 | 68.9 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.7 | 29.0 | 61.8 | 65.1 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.2 | 90.0 | 69.8 | 91.7 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.2 | 68.0 | 60.9 | 75.3 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 41.0 | 89.0 | 64.4 | 86.1 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 43.0 | 76.0 | 57.3 | 81.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.0 | 54.0 | 53.1 | 66.6 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.3 | 19.0 | 51.0 | 55.8 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 15.0 | 53.7 | 58.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.7 | 19.0 | 59.1 | 65.6 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.3 | 17.0 | 58.3 | 64.9 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 34.3 | 48.0 | 61.4 | 66.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.3 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.8 | 87.0 | 74.5 | 127.1 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 29.6 | 69.0 | 63.4 | 103.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 30.6 | 81.0 | 62.8 | 98.7 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.6 | 72.0 | 56.4 | 88.0 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.0 | 50.0 | 48.7 | 71.4 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 18.0 | 53.3 | 59.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.7 | 16.0 | 50.0 | 50.3 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.3 | 19.0 | 58.0 | 65.0 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 17.0 | 57.3 | 65.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.3 | 27.0 | 60.9 | 65.2 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.3 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.4 | 8.4 | 142 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 43.7 | 90.0 | 77.9 | 132.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.5 | 71.0 | 65.8 | 107.3 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.3 | 76.0 | 66.1 | 109.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.8 | 80.0 | 59.4 | 101.7 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.5 | 68.0 | 47.9 | 82.3 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen1 x8 | 0.0 | 0.0 | 8.4 | 8.5 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 18.0 | 57.6 | 80.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 16.0 | 56.8 | 76.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.8 | 18.0 | 60.2 | 83.3 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.5 | 31.0 | 61.5 | 82.8 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.2 | 27.0 | 62.9 | 67.7 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.8 | 142 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 45.8 | 88.0 | 80.5 | 132.6 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.2 | 76.0 | 69.4 | 110.0 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.3 | 76.0 | 68.3 | 109.7 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.2 | 73.0 | 62.9 | 99.1 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.6 | 41.0 | 48.6 | 77.5 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.7 | 19.0 | 57.7 | 69.7 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.0 | 49.0 | 57.6 | 66.1 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 38.3 | 77.0 | 61.1 | 73.3 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.7 | 43.0 | 57.2 | 66.8 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 28.0 | 61.0 | 67.1 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.7 | 142 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 43.7 | 97.0 | 79.8 | 131.4 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 34.0 | 76.0 | 70.5 | 110.8 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 37.0 | 76.0 | 70.3 | 109.5 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 29.3 | 76.0 | 63.4 | 98.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.4 | 50.0 | 53.3 | 79.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.0 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.2 | 18.0 | 56.3 | 79.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.4 | 70.0 | 59.0 | 80.3 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 34.6 | 64.0 | 64.6 | 87.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 33.2 | 87.0 | 60.0 | 81.4 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.6 | 28.0 | 61.8 | 69.8 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.0 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.5 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 43.4 | 96.0 | 77.4 | 130.9 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 28.4 | 75.0 | 67.9 | 107.6 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 33.0 | 91.0 | 69.2 | 111.4 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.1 | 83.0 | 64.3 | 101.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.0 | 67.0 | 54.9 | 87.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.4 | 42.0 | 56.8 | 69.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.8 | 86.0 | 58.1 | 70.0 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.8 | 40.0 | 62.9 | 79.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.2 | 18.0 | 60.5 | 84.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.6 | 27.0 | 62.4 | 76.8 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.5 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

