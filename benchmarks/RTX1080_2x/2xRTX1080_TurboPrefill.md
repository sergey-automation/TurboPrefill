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
- TURBOPREFILL: `1`
- llama_server_log: `/workspace/llama.cpp/bench_reports_gpt-20b/20260605_224145/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
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
| ctx_001_000256.txt | 255 | 128 | 641.20 | 0.40 | 70.67 | 2.22 |
| ctx_002_000512.txt | 504 | 128 | 1108.53 | 0.45 | 69.15 | 2.33 |
| ctx_003_001024.txt | 1017 | 128 | 1136.87 | 0.89 | 68.85 | 2.81 |
| ctx_004_002048.txt | 2044 | 128 | 1189.62 | 1.72 | 67.49 | 3.75 |
| ctx_005_004096.txt | 4076 | 128 | 1451.84 | 2.81 | 68.28 | 4.80 |
| ctx_006_006144.txt | 6142 | 19 | 1466.08 | 4.19 | 67.48 | 4.61 |
| ctx_007_008192.txt | 8164 | 128 | 1476.04 | 5.53 | 66.00 | 7.65 |
| ctx_008_012288.txt | 12280 | 128 | 1375.73 | 8.93 | 64.52 | 11.14 |
| ctx_009_016384.txt | 16373 | 128 | 1301.98 | 12.58 | 63.01 | 14.92 |
| ctx_010_024576.txt | 24560 | 128 | 1077.39 | 22.80 | 59.94 | 25.36 |
| ctx_011_032768.txt | 32761 | 128 | 951.73 | 34.42 | 56.96 | 37.27 |
| ctx_012_065536.txt | 64423 | 128 | 628.61 | 102.48 | 49.87 | 105.91 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 1.0 | 1.0 | 86.7 | 86.7 | 7507 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 0.0 | 0.0 | 60.2 | 60.2 | 7191 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 40.1 | 44.0 | 131.3 | 166.1 | 7507 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 54.0 | 63.0 | 142.8 | 175.7 | 7209 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.0 | 63.0 | 164.1 | 254.9 | 7515 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 24.5 | 48.0 | 142.6 | 208.9 | 7217 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 37.1 | 45.0 | 128.5 | 148.8 | 7515 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 55.7 | 85.0 | 140.4 | 157.1 | 7217 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 66.5 | 100.0 | 118.3 | 192.7 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 9.0 | 31.0 | 91.7 | 162.3 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 41.8 | 46.0 | 134.1 | 149.5 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.0 | 56.0 | 131.4 | 138.5 | 7225 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 65.9 | 100.0 | 104.3 | 158.2 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 17.6 | 37.0 | 102.6 | 155.8 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 39.3 | 45.0 | 134.3 | 161.5 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.9 | 71.0 | 147.2 | 173.1 | 7225 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 62.7 | 100.0 | 128.8 | 166.3 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 53.8 | 100.0 | 110.0 | 186.0 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 39.6 | 47.0 | 139.0 | 165.6 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 57.9 | 96.0 | 147.8 | 164.0 | 7225 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 67.9 | 100.0 | 129.4 | 196.5 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 54.2 | 100.0 | 115.8 | 165.8 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 21.0 | 42.0 | 91.7 | 116.1 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 75.0 | 100.0 | 137.2 | 148.4 | 7225 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 78.2 | 100.0 | 139.8 | 184.9 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 47.5 | 100.0 | 128.8 | 186.8 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 37.9 | 47.0 | 136.4 | 166.8 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 59.0 | 100.0 | 144.1 | 160.3 | 7225 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 78.5 | 100.0 | 141.0 | 230.8 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 59.0 | 100.0 | 123.4 | 229.5 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 35.6 | 47.0 | 127.7 | 153.0 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 61.9 | 93.0 | 137.5 | 163.8 | 7225 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 82.5 | 100.0 | 142.0 | 175.2 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 64.6 | 100.0 | 130.4 | 188.4 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 35.6 | 45.0 | 141.9 | 173.7 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 61.0 | 100.0 | 153.2 | 169.9 | 7225 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 80.3 | 100.0 | 132.9 | 179.2 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 65.0 | 100.0 | 128.4 | 210.9 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 34.1 | 44.0 | 136.0 | 168.5 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 63.0 | 100.0 | 137.3 | 165.2 | 7225 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 80.7 | 100.0 | 138.8 | 183.1 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 67.7 | 100.0 | 126.8 | 233.8 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 34.4 | 47.0 | 129.0 | 169.2 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 63.5 | 100.0 | 145.1 | 168.3 | 7225 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 80.9 | 100.0 | 135.3 | 186.9 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 71.1 | 100.0 | 129.4 | 209.7 | 7225 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 30.5 | 48.0 | 127.7 | 193.8 | 7523 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen3 x8 | 66.8 | 100.0 | 148.0 | 201.3 | 7225 |

