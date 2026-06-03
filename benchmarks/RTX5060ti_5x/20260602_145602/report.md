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
- TURBOPREFILL: `0`
- llama_server_log: `/workspace/bench_reports_gpt-120b_5xRTX5060ti/20260602_145602/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
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
| ctx_001_000256.txt | 2784 | 128 | 1825.35 | 1.53 | 96.83 | 2.87 |
| ctx_002_000512.txt | 255 | 128 | 1074.25 | 0.24 | 100.47 | 1.52 |
| ctx_003_001024.txt | 504 | 128 | 1621.74 | 0.31 | 99.92 | 1.63 |
| ctx_004_002048.txt | 1017 | 128 | 1774.56 | 0.57 | 98.86 | 1.93 |
| ctx_005_004096.txt | 2044 | 128 | 2044.52 | 1.00 | 97.81 | 2.50 |
| ctx_006_006144.txt | 4076 | 128 | 2069.93 | 1.97 | 95.56 | 3.45 |
| ctx_007_008192.txt | 6142 | 128 | 2144.89 | 2.86 | 93.23 | 4.44 |
| ctx_008_012288.txt | 8164 | 128 | 2100.84 | 3.89 | 93.16 | 5.52 |
| ctx_009_016384.txt | 12280 | 128 | 2063.08 | 5.95 | 90.29 | 7.70 |
| ctx_010_024576.txt | 16373 | 128 | 1993.28 | 8.21 | 87.34 | 10.08 |
| ctx_011_032768.txt | 24560 | 128 | 1887.65 | 13.01 | 82.14 | 15.12 |
| ctx_012_065536.txt | 32761 | 128 | 1814.02 | 18.06 | 77.50 | 20.37 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.3 | 3.0 | 42.0 | 51.5 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.3 | 40.0 | 44.1 | 51.2 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.3 | 55.0 | 45.0 | 50.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 34.3 | 54.0 | 44.1 | 49.8 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.3 | 47.0 | 39.4 | 41.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 23.5 | 25.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 21.6 | 25.3 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen2 x8 | 0.0 | 0.0 | 18.0 | 24.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 17.0 | 48.8 | 52.4 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.7 | 16.0 | 51.4 | 52.4 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 19.0 | 51.9 | 53.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.7 | 16.0 | 51.3 | 53.0 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.3 | 29.0 | 54.3 | 62.5 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 17.9 | 20.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 12.2 | 14.1 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen1 x8 | 0.0 | 0.0 | 13.1 | 14.6 | 142 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.0 | 44.0 | 49.6 | 51.8 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.0 | 41.0 | 51.2 | 52.5 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.3 | 40.0 | 49.7 | 50.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.3 | 41.0 | 49.2 | 51.0 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 28.0 | 29.0 | 56.2 | 58.6 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 12.1 | 12.6 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 10.4 | 10.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 11.1 | 11.7 | 142 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 40.0 | 40.0 | 40.6 | 40.6 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 39.6 | 39.6 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 38.5 | 38.5 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.4 | 37.4 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 43.8 | 43.8 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.8 | 9.8 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.0 | 9.0 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.0 | 17.0 | 44.0 | 47.2 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 16.0 | 46.0 | 50.2 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 18.0 | 44.0 | 47.7 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 16.0 | 43.9 | 47.5 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 28.5 | 29.0 | 48.5 | 57.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.4 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.7 | 9.8 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.8 | 9.0 | 142 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 42.6 | 42.6 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 45.6 | 45.6 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 44.1 | 44.1 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 40.4 | 40.4 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 47.2 | 47.2 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 18.0 | 47.3 | 51.6 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 16.0 | 49.0 | 53.0 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.3 | 18.0 | 49.9 | 53.5 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.7 | 63.0 | 49.2 | 53.3 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.7 | 43.0 | 52.1 | 63.8 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.7 | 142 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.0 | 10.0 | 47.0 | 47.1 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.5 | 3.0 | 48.3 | 49.1 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 46.8 | 48.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 44.8 | 45.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.5 | 46.0 | 51.5 | 59.5 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.0 | 46.0 | 54.5 | 57.7 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.0 | 16.0 | 51.5 | 52.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 30.7 | 56.0 | 51.3 | 52.0 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 16.0 | 49.7 | 55.0 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.0 | 29.0 | 47.5 | 57.3 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.5 | 45.0 | 51.3 | 60.4 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.2 | 48.0 | 48.2 | 54.9 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.8 | 68.0 | 44.4 | 50.3 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.5 | 63.0 | 45.2 | 51.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.2 | 1.0 | 39.8 | 46.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 18.0 | 54.8 | 64.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.0 | 32.0 | 52.2 | 55.8 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.7 | 72.0 | 54.2 | 56.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.3 | 66.0 | 54.9 | 56.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.3 | 42.0 | 53.9 | 63.6 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.7 | 142 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.3 | 56.0 | 52.2 | 59.8 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.0 | 67.0 | 48.4 | 54.9 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.5 | 59.0 | 46.8 | 55.9 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 44.0 | 45.1 | 52.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 4.2 | 16.0 | 40.0 | 45.7 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.7 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.3 | 19.0 | 55.0 | 61.7 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 16.0 | 53.7 | 53.8 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.7 | 40.0 | 53.0 | 53.6 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.0 | 16.0 | 51.2 | 51.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 27.0 | 49.6 | 57.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.6 | 9.6 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.2 | 74.0 | 52.9 | 61.5 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.4 | 67.0 | 51.0 | 58.5 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 65.0 | 47.8 | 53.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.4 | 67.0 | 46.9 | 54.1 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.4 | 47.0 | 41.3 | 48.8 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.3 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.5 | 9.7 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.7 | 8.8 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 19.0 | 54.7 | 61.1 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.0 | 15.0 | 53.2 | 55.6 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.0 | 41.0 | 51.2 | 52.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.3 | 19.0 | 50.8 | 52.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 27.0 | 50.5 | 60.2 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.5 | 96.0 | 55.4 | 64.5 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.8 | 72.0 | 51.9 | 57.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.0 | 76.0 | 49.5 | 54.2 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.9 | 50.0 | 47.7 | 54.3 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.5 | 45.0 | 40.7 | 43.0 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.5 | 18.0 | 55.8 | 61.8 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 16.0 | 54.2 | 58.5 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.5 | 18.0 | 53.5 | 56.1 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.0 | 30.0 | 53.9 | 55.9 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 30.2 | 59.0 | 51.1 | 64.4 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.0 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.4 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.6 | 94.0 | 57.2 | 65.5 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.9 | 72.0 | 52.8 | 60.9 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.9 | 70.0 | 50.2 | 58.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.5 | 64.0 | 49.9 | 56.4 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 46.0 | 40.7 | 45.4 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.1 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 36.0 | 93.0 | 54.5 | 63.5 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 16.0 | 53.9 | 56.6 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.8 | 19.0 | 55.4 | 56.9 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.8 | 17.0 | 52.4 | 54.3 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.5 | 27.0 | 50.9 | 60.4 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.2 | 9.4 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.5 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.7 | 84.0 | 58.2 | 67.3 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.5 | 75.0 | 53.1 | 59.2 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.4 | 71.0 | 51.0 | 60.3 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.6 | 76.0 | 50.6 | 57.3 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.9 | 56.0 | 42.5 | 47.9 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.5 | 9.7 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.2 | 18.0 | 54.7 | 66.1 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.8 | 52.0 | 56.1 | 64.3 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.2 | 74.0 | 57.0 | 60.6 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.5 | 37.0 | 53.4 | 55.9 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.0 | 28.0 | 52.5 | 60.4 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.5 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.6 | 8.6 | 142 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.1 | 93.0 | 59.3 | 71.0 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.7 | 86.0 | 56.1 | 64.8 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.9 | 92.0 | 54.4 | 64.8 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.8 | 80.0 | 50.9 | 58.6 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.1 | 58.0 | 42.7 | 52.7 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.1 | 9.2 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.4 | 9.5 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.7 | 142 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.8 | 19.0 | 54.5 | 59.8 | 14424 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.6 | 28.0 | 54.3 | 59.7 | 12398 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.4 | 55.0 | 56.4 | 61.6 | 14162 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 34.4 | 65.0 | 55.8 | 58.2 | 12522 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.8 | 27.0 | 54.0 | 67.0 | 11816 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.5 | 142 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 9.3 | 9.3 | 142 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 8.5 | 8.5 | 142 |

