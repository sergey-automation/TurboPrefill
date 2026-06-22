# llama-server context benchmark report

## Test header

- MODEL: `/workspace/models/gpt-oss-20b-Q4_K_M.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `16384`
- UBATCH: `768`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `0`
- llama_server_log: `/workspace/llama.cpp/bench_reports_gpt-20b/20260605_224543/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
```

### nvidia_smi

```text
0, NVIDIA GeForce GTX 1080 Ti, 570.158.01, 11264 MiB
1, NVIDIA GeForce GTX 1080 Ti, 570.158.01, 11264 MiB
```

### nvcc

```text
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2025 NVIDIA Corporation
Built on Fri_Feb_21_20:23:50_PST_2025
Cuda compilation tools, release 12.8, V12.8.93
Build cuda_12.8.r12.8/compiler.35583870_0
```

### cmake

```text
cmake version 3.28.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Server command

```bash
./build/bin/llama-server -m /workspace/models/gpt-oss-20b-Q4_K_M.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 16384 -ub 768 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 723.52 | 0.35 | 68.69 | 2.22 |
| ctx_002_000512.txt | 504 | 128 | 1063.99 | 0.47 | 68.02 | 2.38 |
| ctx_003_001024.txt | 1017 | 128 | 1099.42 | 0.93 | 67.46 | 2.87 |
| ctx_004_002048.txt | 2044 | 128 | 1135.03 | 1.80 | 65.28 | 3.85 |
| ctx_005_004096.txt | 4076 | 128 | 1096.10 | 3.72 | 65.25 | 5.78 |
| ctx_006_006144.txt | 6142 | 128 | 1073.86 | 5.72 | 66.32 | 7.80 |
| ctx_007_008192.txt | 8164 | 128 | 1008.86 | 8.09 | 64.76 | 10.28 |
| ctx_008_012288.txt | 12280 | 128 | 918.39 | 13.37 | 63.73 | 15.61 |
| ctx_009_016384.txt | 16373 | 128 | 835.64 | 19.59 | 61.97 | 22.01 |
| ctx_010_024576.txt | 24560 | 128 | 709.88 | 34.60 | 59.82 | 37.17 |
| ctx_011_032768.txt | 32761 | 128 | 616.60 | 53.13 | 57.19 | 55.93 |
| ctx_012_065536.txt | 64423 | 128 | 407.97 | 157.91 | 50.07 | 161.32 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 0.0 | 0.0 | 168.3 | 168.3 | 7507 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 0.0 | 0.0 | 66.7 | 66.7 | 7191 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 41.9 | 45.0 | 137.9 | 151.1 | 7507 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 54.1 | 60.0 | 143.4 | 166.3 | 7209 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 70.0 | 100.0 | 164.2 | 259.4 | 7515 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 27.0 | 54.0 | 111.1 | 141.9 | 7217 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 40.9 | 45.0 | 148.0 | 167.4 | 7515 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 54.7 | 61.0 | 151.1 | 173.4 | 7217 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 56.0 | 83.0 | 97.2 | 156.3 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 39.2 | 58.0 | 103.4 | 154.4 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 42.1 | 44.0 | 147.5 | 165.8 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 52.9 | 54.0 | 142.9 | 156.9 | 7225 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 66.7 | 100.0 | 109.4 | 162.1 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 26.1 | 100.0 | 107.6 | 157.1 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 36.6 | 43.0 | 145.6 | 163.1 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 56.6 | 97.0 | 143.9 | 161.1 | 7225 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.6 | 100.0 | 117.5 | 172.2 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 33.2 | 100.0 | 104.4 | 162.6 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 39.0 | 45.0 | 137.3 | 151.3 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.0 | 63.0 | 145.8 | 161.3 | 7225 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 49.4 | 100.0 | 126.2 | 185.1 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 40.3 | 100.0 | 100.1 | 168.8 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 41.0 | 49.0 | 136.3 | 164.4 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 56.6 | 75.0 | 152.4 | 173.2 | 7225 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 55.1 | 100.0 | 116.6 | 160.4 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 40.1 | 100.0 | 108.6 | 172.3 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 33.0 | 47.0 | 135.6 | 166.3 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 64.4 | 100.0 | 148.4 | 173.4 | 7225 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 57.2 | 100.0 | 120.0 | 188.2 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 38.3 | 100.0 | 104.8 | 215.9 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 34.4 | 45.0 | 142.4 | 174.7 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 63.1 | 100.0 | 138.8 | 160.6 | 7225 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 57.8 | 100.0 | 116.6 | 174.3 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 39.9 | 100.0 | 103.9 | 197.8 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 33.6 | 46.0 | 131.1 | 163.5 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 63.2 | 100.0 | 138.5 | 171.4 | 7225 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 54.3 | 100.0 | 115.6 | 173.4 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 42.8 | 100.0 | 106.0 | 203.9 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 34.7 | 46.0 | 133.5 | 171.3 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 62.9 | 100.0 | 143.1 | 169.8 | 7225 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.8 | 100.0 | 113.7 | 262.1 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 47.1 | 100.0 | 109.7 | 197.9 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 31.8 | 46.0 | 130.9 | 166.7 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 66.2 | 100.0 | 145.3 | 169.9 | 7225 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 52.8 | 100.0 | 112.3 | 203.4 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 46.4 | 100.0 | 108.7 | 199.1 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 33.5 | 48.0 | 128.5 | 198.6 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 67.1 | 100.0 | 142.0 | 190.1 | 7225 |

