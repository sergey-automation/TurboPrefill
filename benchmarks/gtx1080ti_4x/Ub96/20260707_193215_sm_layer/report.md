# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `96`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `0`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_193215/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
```

### nvidia_smi

```text
0, NVIDIA GeForce GTX 1080 Ti, 580.159.03, 11264 MiB
1, NVIDIA GeForce GTX 1080 Ti, 580.159.03, 11264 MiB
2, NVIDIA GeForce GTX 1080 Ti, 580.159.03, 11264 MiB
3, NVIDIA GeForce GTX 1080 Ti, 580.159.03, 11264 MiB
4, NVIDIA GeForce GTX 1080 Ti, 580.159.03, 11264 MiB
5, NVIDIA GeForce GTX 1080 Ti, 580.159.03, 11264 MiB
```

### nvcc

```text
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2024 NVIDIA Corporation
Built on Thu_Mar_28_02:18:24_PDT_2024
Cuda compilation tools, release 12.4, V12.4.131
Build cuda_12.4.r12.4/compiler.34097967_0
```

### cmake

```text
cmake version 4.2.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Server command

```bash
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 96 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 136.58 | 1.87 | 47.89 | 5.71 |
| ctx_002_000512.txt | 504 | 128 | 298.57 | 1.69 | 49.79 | 5.28 |
| ctx_003_001024.txt | 1017 | 128 | 338.41 | 3.01 | 49.78 | 6.27 |
| ctx_004_002048.txt | 2044 | 128 | 418.15 | 4.89 | 49.43 | 8.59 |
| ctx_005_004096.txt | 4076 | 128 | 425.05 | 9.59 | 47.88 | 13.02 |
| ctx_006_006144.txt | 6142 | 128 | 431.99 | 14.22 | 47.66 | 17.45 |
| ctx_007_008192.txt | 8164 | 106 | 430.79 | 18.95 | 50.03 | 21.82 |
| ctx_008_012288.txt | 12280 | 128 | 412.98 | 29.73 | 49.44 | 33.16 |
| ctx_009_016384.txt | 16373 | 128 | 403.47 | 40.58 | 49.27 | 44.14 |
| ctx_010_024576.txt | 24560 | 128 | 370.41 | 66.31 | 46.90 | 70.29 |
| ctx_011_032768.txt | 32761 | 128 | 343.78 | 95.30 | 44.41 | 99.85 |
| ctx_012_065536.txt | 64423 | 128 | 258.75 | 248.97 | 38.49 | 254.59 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.6 | 4.0 | 59.4 | 61.3 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 62.6 | 62.8 | 3358 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 76.6 | 76.7 | 3358 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.7 | 12.0 | 74.7 | 74.8 | 4066 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.2 | 40.0 | 71.5 | 85.2 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.4 | 37.0 | 72.6 | 84.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.7 | 32.0 | 99.6 | 194.6 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.8 | 38.0 | 109.5 | 136.4 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.3 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.0 | 39.0 | 59.4 | 59.6 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 7.0 | 36.0 | 63.1 | 63.3 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 4.2 | 19.0 | 75.9 | 77.4 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 3.5 | 17.0 | 78.9 | 93.4 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.2 | 12.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.2 | 37.0 | 79.7 | 152.9 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 33.0 | 81.2 | 136.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.5 | 34.0 | 109.7 | 234.9 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.6 | 41.0 | 124.9 | 157.6 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 10.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.3 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 12.3 | 32.0 | 116.2 | 159.5 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 9.9 | 33.0 | 78.5 | 144.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.3 | 29.0 | 82.8 | 148.5 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 12.7 | 21.0 | 76.6 | 77.0 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.2 | 12.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.2 | 38.0 | 74.8 | 92.0 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.6 | 31.0 | 77.7 | 89.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.4 | 18.0 | 111.3 | 199.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 40.0 | 119.3 | 159.3 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.8 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.2 | 39.0 | 77.3 | 157.9 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.0 | 35.0 | 80.2 | 145.4 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.7 | 29.0 | 96.4 | 219.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 10.5 | 19.0 | 90.3 | 220.8 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.1 | 39.0 | 82.5 | 154.8 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.8 | 40.0 | 76.1 | 88.4 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 34.0 | 93.2 | 162.3 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.2 | 40.0 | 120.9 | 153.5 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.3 | 40.0 | 93.6 | 163.4 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.5 | 36.0 | 85.4 | 152.1 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.3 | 36.0 | 72.8 | 143.7 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.7 | 24.0 | 95.9 | 210.0 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 12.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.6 | 39.0 | 75.0 | 80.0 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.4 | 37.0 | 83.0 | 152.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.3 | 36.0 | 69.7 | 74.6 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.4 | 48.0 | 99.8 | 114.5 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 28.2 | 40.0 | 92.9 | 180.3 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.5 | 39.0 | 86.8 | 154.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.5 | 38.0 | 79.4 | 146.9 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.7 | 27.0 | 92.6 | 186.9 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.1 | 29.0 | 93.9 | 135.3 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.4 | 40.0 | 83.1 | 91.4 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.8 | 39.0 | 75.6 | 84.6 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.7 | 38.0 | 114.5 | 130.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 28.4 | 41.0 | 95.0 | 186.2 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.4 | 40.0 | 86.5 | 161.3 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.0 | 43.0 | 88.3 | 165.7 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.2 | 25.0 | 106.3 | 233.6 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.4 | 40.0 | 94.4 | 119.3 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.2 | 41.0 | 91.0 | 104.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 28.0 | 84.2 | 95.6 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.3 | 41.0 | 144.7 | 230.6 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.4 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.3 | 41.0 | 121.6 | 247.9 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.5 | 40.0 | 105.8 | 243.2 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.0 | 41.0 | 84.4 | 181.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.4 | 32.0 | 80.3 | 145.5 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.5 | 42.0 | 117.2 | 166.9 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.8 | 35.0 | 113.1 | 146.2 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.2 | 28.0 | 115.7 | 216.7 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.3 | 44.0 | 117.1 | 158.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.9 | 44.0 | 127.8 | 268.8 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.8 | 55.0 | 115.1 | 261.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.3 | 54.0 | 104.0 | 254.0 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 37.0 | 90.6 | 233.9 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.8 | 43.0 | 124.3 | 153.8 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 43.0 | 142.1 | 250.5 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.1 | 43.0 | 102.5 | 126.1 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.2 | 45.0 | 117.6 | 160.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.7 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.2 | 52.0 | 136.8 | 273.1 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.6 | 73.0 | 120.8 | 274.2 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.8 | 50.0 | 114.2 | 248.6 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.4 | 72.0 | 96.7 | 246.6 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.2 | 51.0 | 134.7 | 231.8 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.8 | 26.0 | 135.1 | 216.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.2 | 50.0 | 113.4 | 240.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 46.0 | 136.1 | 178.7 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.4 | 8.8 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.9 | 55.0 | 137.1 | 275.6 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.4 | 85.0 | 126.1 | 269.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.9 | 88.0 | 117.5 | 250.5 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.2 | 80.0 | 96.8 | 252.0 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 13.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.8 | 54.0 | 132.5 | 241.5 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.1 | 36.0 | 116.0 | 265.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.0 | 30.0 | 110.8 | 252.4 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.6 | 56.0 | 146.8 | 229.4 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.7 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.9 | 76.0 | 139.5 | 277.2 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.0 | 85.0 | 127.4 | 268.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.8 | 87.0 | 113.9 | 251.3 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.0 | 100.0 | 118.9 | 272.8 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.4 | 74.0 | 118.2 | 238.7 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.4 | 70.0 | 125.4 | 244.5 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.5 | 86.0 | 104.7 | 238.4 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.7 | 77.0 | 162.3 | 244.1 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.3 | 146 |

