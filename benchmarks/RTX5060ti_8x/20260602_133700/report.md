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
- TURBOPREFILL: `0`
- llama_server_log: `/workspace/bench_reports_gpt-120b_8xRTX5060ti/20260602_133700/llama_server.log`

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
./build/bin/llama-server -m /workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66032 -b 16384 -ub 768 -np 1 -ctk f16 -sm layer -ts 1/1/1/1/1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 2784 | 128 | 1773.57 | 1.57 | 95.36 | 2.94 |
| ctx_002_000512.txt | 255 | 128 | 1038.38 | 0.25 | 98.70 | 1.69 |
| ctx_003_001024.txt | 504 | 128 | 1609.21 | 0.31 | 98.42 | 1.65 |
| ctx_004_002048.txt | 1017 | 128 | 1761.58 | 0.58 | 97.45 | 1.96 |
| ctx_005_004096.txt | 2044 | 128 | 2020.91 | 1.01 | 96.39 | 2.45 |
| ctx_006_006144.txt | 4076 | 128 | 2046.48 | 1.99 | 94.25 | 3.53 |
| ctx_007_008192.txt | 6142 | 128 | 2122.23 | 2.89 | 91.95 | 4.49 |
| ctx_008_012288.txt | 8164 | 128 | 2076.07 | 3.93 | 91.80 | 5.63 |
| ctx_009_016384.txt | 12280 | 128 | 2034.73 | 6.04 | 89.06 | 7.84 |
| ctx_010_024576.txt | 16373 | 128 | 1963.16 | 8.34 | 86.19 | 10.31 |
| ctx_011_032768.txt | 24560 | 128 | 1852.98 | 13.25 | 81.04 | 15.44 |
| ctx_012_065536.txt | 32761 | 128 | 1775.95 | 18.45 | 76.51 | 20.96 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 2.0 | 36.4 | 37.0 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.3 | 37.0 | 41.6 | 44.6 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 34.9 | 35.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 38.6 | 41.9 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.5 | 36.6 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.3 | 4.0 | 38.0 | 40.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.0 | 39.0 | 37.6 | 38.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 20.0 | 32.7 | 35.2 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 11.0 | 40.3 | 41.5 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.0 | 11.0 | 43.7 | 44.2 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.8 | 29.0 | 38.4 | 38.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.5 | 24.0 | 43.4 | 46.3 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.2 | 27.0 | 41.2 | 41.8 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 16.0 | 38.0 | 43.5 | 45.2 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 44.2 | 46.2 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.0 | 22.0 | 45.4 | 55.2 | 6964 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.0 | 36.0 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 39.9 | 39.9 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 34.9 | 34.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 37.1 | 37.1 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.1 | 37.1 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 35.6 | 35.6 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.1 | 37.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.0 | 1.0 | 45.3 | 45.3 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 11.0 | 37.6 | 39.5 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 41.2 | 43.1 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.3 | 9.0 | 36.0 | 37.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 39.2 | 41.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 37.6 | 40.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 9.0 | 38.4 | 40.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 39.3 | 41.4 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.0 | 22.0 | 47.9 | 55.6 | 6964 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 46.0 | 46.0 | 42.5 | 42.5 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.0 | 22.0 | 42.2 | 42.2 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.4 | 35.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 38.2 | 38.2 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.5 | 37.5 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.9 | 36.9 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.9 | 37.9 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 47.5 | 47.5 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.3 | 11.0 | 39.5 | 39.5 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 43.2 | 43.5 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 9.0 | 37.0 | 37.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 41.1 | 41.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 11.0 | 40.3 | 41.9 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 9.0 | 40.5 | 41.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 11.0 | 41.8 | 43.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.7 | 22.0 | 50.1 | 55.3 | 6964 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 14.0 | 37.0 | 37.0 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 40.1 | 40.1 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.1 | 35.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.2 | 37.2 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.7 | 36.7 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 35.9 | 35.9 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.3 | 37.3 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 46.1 | 46.1 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.7 | 11.0 | 40.9 | 41.4 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 11.0 | 44.6 | 45.0 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.7 | 36.0 | 37.7 | 39.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.3 | 33.0 | 41.5 | 42.6 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.7 | 18.0 | 39.0 | 41.9 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.7 | 35.0 | 41.4 | 43.6 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.7 | 46.0 | 41.7 | 44.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.7 | 22.0 | 42.4 | 51.0 | 6964 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 37.8 | 40.1 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.0 | 26.0 | 40.0 | 40.7 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 33.3 | 33.5 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 3.5 | 7.0 | 35.6 | 36.2 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.5 | 1.0 | 34.8 | 35.1 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.5 | 1.0 | 34.8 | 35.0 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.5 | 1.0 | 34.9 | 35.2 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 36.7 | 42.8 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 11.0 | 42.4 | 44.4 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 12.0 | 46.2 | 47.5 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.0 | 9.0 | 37.3 | 38.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.0 | 43.0 | 42.1 | 44.3 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 33.0 | 41.7 | 43.5 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.3 | 37.0 | 42.4 | 44.0 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.3 | 46.0 | 45.1 | 46.8 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 22.0 | 42.3 | 53.0 | 6964 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 4.0 | 14.0 | 40.5 | 45.7 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.5 | 54.0 | 43.9 | 49.0 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 33.0 | 36.7 | 40.3 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.5 | 45.0 | 40.0 | 43.6 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.5 | 38.0 | 36.2 | 40.1 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.5 | 38.0 | 38.2 | 46.1 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.5 | 47.0 | 39.0 | 47.2 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 0.0 | 0.0 | 34.6 | 43.7 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.5 | 12.0 | 43.1 | 46.0 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.2 | 55.0 | 47.4 | 53.4 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.2 | 40.0 | 39.9 | 42.4 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.2 | 47.0 | 43.7 | 45.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 11.0 | 42.3 | 43.6 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.8 | 9.0 | 42.1 | 44.5 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.8 | 12.0 | 42.7 | 46.3 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.5 | 22.0 | 44.6 | 55.4 | 6964 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.0 | 56.0 | 42.1 | 45.6 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.7 | 53.0 | 45.1 | 48.7 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 3.7 | 22.0 | 37.1 | 40.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.0 | 36.0 | 41.1 | 45.8 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 44.0 | 39.4 | 44.0 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.7 | 36.0 | 39.5 | 42.0 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.7 | 47.0 | 40.8 | 46.6 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.3 | 19.0 | 35.9 | 46.2 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 22.5 | 58.0 | 41.4 | 44.4 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.2 | 41.0 | 44.9 | 46.9 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.8 | 9.0 | 38.4 | 39.3 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 11.0 | 42.1 | 43.1 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 41.7 | 42.1 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 10.0 | 41.8 | 42.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 44.3 | 46.3 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.0 | 20.0 | 44.4 | 55.2 | 6964 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.4 | 58.0 | 42.7 | 46.3 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.8 | 39.0 | 46.3 | 49.9 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 40.0 | 38.7 | 40.6 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.9 | 49.0 | 41.8 | 44.4 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.4 | 47.0 | 38.9 | 42.3 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.7 | 37.0 | 40.7 | 43.5 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.6 | 46.0 | 41.4 | 44.4 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.6 | 20.0 | 35.0 | 49.6 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.8 | 12.0 | 40.5 | 45.6 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.5 | 47.0 | 46.0 | 49.6 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.8 | 9.0 | 38.6 | 39.3 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.8 | 50.0 | 43.7 | 48.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.0 | 46.0 | 42.5 | 45.1 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.0 | 9.0 | 41.5 | 43.1 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.2 | 16.0 | 42.4 | 46.2 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.5 | 21.0 | 44.8 | 54.4 | 6964 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 29.0 | 43.3 | 46.8 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 21.1 | 59.0 | 47.5 | 51.0 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.0 | 41.0 | 38.5 | 43.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.4 | 49.0 | 42.4 | 46.2 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.9 | 44.0 | 40.0 | 44.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.3 | 42.0 | 41.4 | 44.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.7 | 50.0 | 41.1 | 45.5 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 2.8 | 14.0 | 33.9 | 47.6 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.0 | 11.0 | 39.4 | 41.1 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.2 | 11.0 | 46.8 | 50.0 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 4.5 | 9.0 | 38.1 | 40.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.5 | 11.0 | 42.5 | 44.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.5 | 12.0 | 41.4 | 43.5 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.8 | 9.0 | 44.9 | 45.7 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.8 | 50.0 | 46.2 | 47.1 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.0 | 21.0 | 43.4 | 55.5 | 6964 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 19.6 | 59.0 | 43.8 | 48.7 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 17.7 | 63.0 | 47.6 | 53.1 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.6 | 40.0 | 39.0 | 43.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.2 | 26.0 | 41.7 | 46.0 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.5 | 43.0 | 39.7 | 45.8 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.9 | 43.0 | 40.8 | 45.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.2 | 51.0 | 41.8 | 46.8 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 25.0 | 33.6 | 43.2 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.5 | 18.0 | 41.2 | 46.2 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 24.8 | 65.0 | 46.6 | 50.9 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.8 | 20.0 | 38.4 | 40.7 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.0 | 26.0 | 42.6 | 45.1 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 11.0 | 42.2 | 44.4 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.5 | 9.0 | 42.5 | 45.8 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.2 | 12.0 | 43.2 | 45.7 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.8 | 20.0 | 44.4 | 53.7 | 6964 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 26.1 | 71.0 | 44.9 | 50.8 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 69.0 | 48.2 | 54.8 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.2 | 47.0 | 39.3 | 43.9 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.0 | 53.0 | 42.1 | 47.9 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.2 | 55.0 | 39.5 | 46.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.7 | 46.0 | 41.3 | 46.3 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.5 | 53.0 | 41.5 | 46.3 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 1.9 | 25.0 | 33.0 | 38.2 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 23.5 | 61.0 | 43.3 | 50.1 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 20.5 | 45.0 | 48.3 | 51.8 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.8 | 9.0 | 38.1 | 40.0 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 42.1 | 43.6 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.5 | 13.0 | 40.9 | 42.2 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.8 | 9.0 | 41.4 | 43.4 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 8.5 | 12.0 | 42.3 | 44.0 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.2 | 19.0 | 43.2 | 53.0 | 6964 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 10.9 | 66.0 | 43.2 | 50.4 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.4 | 64.0 | 48.5 | 55.4 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 11.1 | 53.0 | 39.5 | 44.2 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 13.7 | 61.0 | 43.5 | 48.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.6 | 60.0 | 41.7 | 48.8 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 14.5 | 48.0 | 42.6 | 47.7 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 15.7 | 56.0 | 42.3 | 48.4 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.6 | 28.0 | 34.2 | 41.8 | 6964 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.8 | 12.0 | 44.0 | 50.2 | 9688 |
| 1 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 6.3 | 13.0 | 44.7 | 49.4 | 9310 |
| 2 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 4.7 | 10.0 | 38.5 | 42.1 | 7544 |
| 3 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 5.7 | 12.0 | 42.9 | 48.7 | 9182 |
| 4 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 7.3 | 13.0 | 42.2 | 46.6 | 9310 |
| 5 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 12.0 | 38.0 | 44.3 | 47.0 | 7546 |
| 6 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 9.2 | 12.0 | 46.8 | 49.4 | 9184 |
| 7 | NVIDIA GeForce RTX 5060 Ti | Gen4 x8 | 18.0 | 35.0 | 43.2 | 52.8 | 6964 |

