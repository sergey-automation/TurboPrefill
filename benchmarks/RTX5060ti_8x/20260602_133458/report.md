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
- TENSOR_SPLIT: `1/1/1/1/1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/workspace/bench_reports_gpt-120b_8xRTX5060ti/20260602_133458/llama_server.log`

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
./build/bin/llama-server -m /workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66032 -b 16384 -ub 768 -np 1 -ctk f16 -sm layer -ts 1/1/1/1/1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 2784 | 128 | 1938.92 | 1.44 | 95.34 | 2.81 |
| ctx_002_000512.txt | 255 | 128 | 1042.57 | 0.24 | 98.64 | 1.69 |
| ctx_003_001024.txt | 504 | 128 | 1613.11 | 0.31 | 98.41 | 1.65 |
| ctx_004_002048.txt | 1017 | 128 | 1764.64 | 0.58 | 97.43 | 1.96 |
| ctx_005_004096.txt | 2044 | 128 | 2022.19 | 1.01 | 96.35 | 2.45 |
| ctx_006_006144.txt | 4076 | 128 | 3179.78 | 1.28 | 94.22 | 2.82 |
| ctx_007_008192.txt | 6142 | 128 | 3668.06 | 1.67 | 91.95 | 3.29 |
| ctx_008_012288.txt | 8164 | 101 | 4111.39 | 1.99 | 91.89 | 3.38 |
| ctx_009_016384.txt | 12280 | 128 | 4421.12 | 2.78 | 89.04 | 4.58 |
| ctx_010_024576.txt | 16373 | 128 | 4380.28 | 3.74 | 86.25 | 5.67 |
| ctx_011_032768.txt | 24560 | 128 | 3684.10 | 6.67 | 81.05 | 8.86 |
| ctx_012_065536.txt | 32761 | 79 | 3359.49 | 9.75 | 76.68 | 11.61 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.7 | 38.0 | 39.1 | 42.5 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.7 | 37.0 | 42.3 | 45.7 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.7 | 39.0 | 37.2 | 39.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 30.7 | 59.0 | 38.2 | 40.3 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.0 | 61.0 | 39.0 | 41.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.7 | 17.0 | 35.6 | 37.7 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.7 | 35.0 | 37.6 | 40.9 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 32.7 | 33.3 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 11.0 | 41.7 | 43.5 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.7 | 12.0 | 42.4 | 45.9 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.7 | 9.0 | 39.1 | 41.6 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 12.0 | 41.6 | 46.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 11.0 | 46.3 | 48.9 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.3 | 36.0 | 41.9 | 44.6 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.0 | 43.0 | 45.1 | 47.2 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.3 | 21.0 | 43.9 | 53.8 | 6964 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.6 | 35.6 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.6 | 37.6 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 33.7 | 33.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.5 | 35.5 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 2.0 | 2.0 | 35.2 | 35.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 33.6 | 33.6 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 34.7 | 34.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 43.3 | 43.3 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.0 | 11.0 | 36.4 | 38.7 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.0 | 11.0 | 39.0 | 41.4 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.3 | 9.0 | 35.5 | 37.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 37.4 | 39.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 36.9 | 39.4 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 9.0 | 36.6 | 38.5 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 38.5 | 40.3 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.7 | 22.0 | 46.6 | 55.5 | 6964 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.0 | 32.0 | 40.0 | 40.0 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 39.3 | 39.3 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.7 | 35.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.1 | 37.1 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.9 | 35.9 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.9 | 35.9 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.0 | 36.0 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 48.1 | 48.1 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 39.1 | 39.2 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 41.4 | 41.5 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 9.0 | 37.5 | 38.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 39.3 | 40.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 39.3 | 40.1 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 9.0 | 38.2 | 38.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 40.5 | 41.9 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.7 | 21.0 | 49.7 | 55.5 | 6964 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.3 | 36.3 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 38.7 | 38.7 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.2 | 35.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.1 | 36.1 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.7 | 35.7 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.1 | 35.1 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.2 | 35.2 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 45.9 | 45.9 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 11.0 | 40.3 | 41.2 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 11.0 | 40.8 | 41.4 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.0 | 9.0 | 36.9 | 38.3 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.3 | 42.0 | 39.7 | 41.5 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.0 | 41.0 | 39.2 | 40.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 36.0 | 38.8 | 40.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.7 | 46.0 | 41.0 | 42.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.3 | 22.0 | 44.6 | 55.5 | 6964 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.0 | 10.0 | 34.4 | 35.3 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.3 | 36.8 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 33.1 | 33.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.5 | 1.0 | 34.1 | 34.3 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 34.1 | 34.6 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.5 | 20.0 | 32.7 | 33.1 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.5 | 1.0 | 33.2 | 34.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.6 | 41.9 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.0 | 11.0 | 40.9 | 42.1 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 11.0 | 42.7 | 44.0 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 9.0 | 37.9 | 38.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 39.8 | 40.5 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.0 | 42.0 | 40.5 | 42.5 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 9.0 | 39.0 | 42.2 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.5 | 15.0 | 41.2 | 44.6 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 22.0 | 45.0 | 55.5 | 6964 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.7 | 50.0 | 50.0 | 57.6 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 38.0 | 83.0 | 50.2 | 56.5 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.7 | 62.0 | 41.6 | 48.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 30.3 | 69.0 | 41.9 | 48.5 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.7 | 45.0 | 39.9 | 49.8 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.7 | 57.0 | 39.8 | 49.9 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.3 | 24.0 | 37.7 | 48.5 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 3.0 | 8.0 | 38.3 | 46.1 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.3 | 10.0 | 46.3 | 53.4 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 11.0 | 50.0 | 60.4 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 9.0 | 45.1 | 52.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 46.6 | 55.8 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.3 | 12.0 | 47.7 | 54.7 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 9.0 | 50.9 | 60.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 11.0 | 48.8 | 55.6 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.7 | 22.0 | 47.1 | 55.5 | 6964 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.2 | 85.0 | 53.5 | 70.4 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.0 | 84.0 | 53.6 | 75.5 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.0 | 32.0 | 43.6 | 57.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.8 | 23.0 | 46.3 | 63.3 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.8 | 64.0 | 45.8 | 65.3 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.8 | 52.0 | 44.9 | 63.9 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.8 | 79.0 | 44.5 | 65.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 35.0 | 38.1 | 43.1 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.3 | 12.0 | 40.6 | 41.0 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 11.0 | 45.1 | 47.1 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.7 | 10.0 | 41.7 | 43.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.7 | 12.0 | 45.2 | 48.2 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 11.0 | 47.5 | 50.3 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.7 | 9.0 | 49.6 | 56.0 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 12.0 | 50.9 | 60.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.0 | 27.0 | 47.4 | 55.6 | 6964 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.5 | 68.0 | 55.8 | 88.6 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 56.0 | 54.6 | 84.5 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.2 | 41.0 | 44.8 | 69.5 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.2 | 59.0 | 48.3 | 76.9 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.8 | 52.0 | 45.8 | 74.5 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.2 | 56.0 | 43.3 | 70.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.8 | 86.0 | 43.2 | 74.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 39.0 | 36.7 | 44.5 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.3 | 23.0 | 47.3 | 58.3 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.0 | 11.0 | 55.4 | 71.2 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 4.7 | 10.0 | 47.0 | 60.5 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 11.0 | 53.4 | 67.5 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 11.0 | 54.1 | 72.9 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.3 | 10.0 | 57.6 | 69.3 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 11.0 | 59.1 | 78.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.3 | 20.0 | 46.3 | 49.6 | 6964 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 37.2 | 88.0 | 64.9 | 113.3 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 36.7 | 88.0 | 66.3 | 115.1 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.2 | 68.0 | 52.9 | 86.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.5 | 63.0 | 53.7 | 81.6 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.5 | 52.0 | 50.3 | 79.4 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.3 | 44.0 | 48.8 | 81.5 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.3 | 56.0 | 49.9 | 87.8 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.8 | 32.0 | 40.1 | 56.8 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.8 | 11.0 | 45.5 | 55.7 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 12.0 | 49.7 | 64.3 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.0 | 9.0 | 44.1 | 57.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 11.0 | 46.8 | 60.6 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 47.7 | 61.5 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.5 | 9.0 | 51.3 | 69.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.0 | 11.0 | 54.3 | 70.9 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.2 | 21.0 | 45.9 | 54.3 | 6964 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 39.0 | 91.0 | 64.5 | 116.8 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.0 | 90.0 | 66.1 | 117.7 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.6 | 55.0 | 52.3 | 88.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 34.5 | 94.0 | 54.3 | 93.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 35.9 | 78.0 | 49.9 | 90.0 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.4 | 50.0 | 48.7 | 86.5 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.2 | 76.0 | 48.3 | 89.6 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.9 | 36.0 | 38.2 | 55.7 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 36.0 | 44.3 | 56.8 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.2 | 36.0 | 49.2 | 71.6 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.8 | 15.0 | 44.2 | 59.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.2 | 11.0 | 47.6 | 60.8 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.4 | 26.0 | 52.1 | 70.3 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.2 | 10.0 | 54.0 | 71.3 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.6 | 27.0 | 55.0 | 78.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.0 | 33.0 | 49.5 | 54.1 | 6964 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 33.7 | 83.0 | 63.8 | 112.9 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.1 | 77.0 | 66.2 | 116.0 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.6 | 50.0 | 52.9 | 84.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.3 | 55.0 | 56.1 | 90.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.9 | 51.0 | 55.4 | 90.0 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.0 | 42.0 | 54.3 | 87.0 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 29.1 | 69.0 | 54.2 | 93.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.3 | 51.0 | 39.7 | 60.4 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 12.0 | 41.8 | 44.9 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.2 | 12.0 | 47.2 | 53.9 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.4 | 9.0 | 43.5 | 52.0 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.6 | 11.0 | 47.0 | 59.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.2 | 12.0 | 49.0 | 62.6 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.6 | 50.0 | 50.6 | 65.6 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 27.6 | 59.0 | 53.1 | 75.5 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.4 | 25.0 | 48.7 | 53.4 | 6964 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 32.5 | 94.0 | 58.9 | 118.1 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.1 | 78.0 | 62.9 | 115.3 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.3 | 66.0 | 49.6 | 81.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.2 | 62.0 | 52.0 | 89.2 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.6 | 74.0 | 53.2 | 91.3 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.6 | 63.0 | 51.1 | 88.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.3 | 79.0 | 51.5 | 89.9 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 53.0 | 38.9 | 60.9 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.8 | 12.0 | 43.1 | 45.1 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.2 | 34.0 | 49.4 | 51.2 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 25.5 | 55.0 | 44.3 | 51.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 31.0 | 66.0 | 48.1 | 56.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.8 | 70.0 | 54.2 | 68.4 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.0 | 10.0 | 54.8 | 71.3 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.0 | 10.0 | 54.3 | 72.0 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.8 | 20.0 | 51.4 | 55.6 | 6964 |

