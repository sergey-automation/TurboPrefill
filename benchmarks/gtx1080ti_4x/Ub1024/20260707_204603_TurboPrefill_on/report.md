# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `1024`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_204603/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 1024 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 200.43 | 1.27 | 50.22 | 5.10 |
| ctx_002_000512.txt | 504 | 128 | 504.71 | 1.00 | 50.74 | 4.13 |
| ctx_003_001024.txt | 1017 | 128 | 679.56 | 1.50 | 52.01 | 4.79 |
| ctx_004_002048.txt | 2044 | 128 | 889.58 | 2.30 | 52.16 | 5.61 |
| ctx_005_004096.txt | 4076 | 128 | 1070.22 | 3.81 | 52.03 | 7.19 |
| ctx_006_006144.txt | 6142 | 45 | 1288.34 | 4.77 | 52.04 | 6.42 |
| ctx_007_008192.txt | 8164 | 128 | 1334.98 | 6.12 | 50.13 | 9.67 |
| ctx_008_012288.txt | 12280 | 128 | 1198.43 | 10.25 | 49.16 | 13.81 |
| ctx_009_016384.txt | 16373 | 115 | 1172.55 | 13.96 | 48.73 | 17.39 |
| ctx_010_024576.txt | 24560 | 128 | 980.57 | 25.05 | 45.89 | 29.21 |
| ctx_011_032768.txt | 32761 | 128 | 844.13 | 38.81 | 44.76 | 43.43 |
| ctx_012_065536.txt | 64423 | 128 | 547.94 | 117.57 | 37.03 | 123.41 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.7 | 58.8 | 6344 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 84.1 | 84.2 | 4044 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 75.4 | 75.5 | 4044 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.5 | 74.6 | 5314 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.8 | 41.0 | 74.2 | 91.2 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.4 | 45.0 | 94.9 | 114.1 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 11.5 | 18.0 | 102.7 | 177.5 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.2 | 42.0 | 109.2 | 143.1 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.5 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 148 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 59.9 | 60.0 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 62.7 | 62.8 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.8 | 7.0 | 58.1 | 58.1 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.2 | 5.0 | 75.4 | 75.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.0 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 11.7 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.6 | 82.0 | 85.4 | 104.2 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.0 | 20.0 | 90.1 | 151.0 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.2 | 86.0 | 78.0 | 93.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.8 | 39.0 | 123.6 | 152.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.6 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 148 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 2.2 | 10.0 | 81.4 | 144.6 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 4.0 | 11.0 | 67.8 | 67.9 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.8 | 14.0 | 62.8 | 63.0 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.2 | 41.0 | 76.1 | 76.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.8 | 99.0 | 91.4 | 113.9 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.2 | 58.0 | 113.6 | 170.7 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.2 | 100.0 | 98.9 | 186.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.8 | 70.0 | 135.7 | 246.9 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.9 | 148 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 6.6 | 51.0 | 94.8 | 248.8 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.5 | 100.0 | 86.9 | 109.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 12.0 | 82.0 | 72.3 | 76.7 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.2 | 87.0 | 99.9 | 264.8 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.6 | 100.0 | 96.7 | 118.3 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.1 | 92.0 | 108.9 | 133.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.3 | 100.0 | 97.4 | 138.4 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.2 | 70.0 | 137.0 | 247.1 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 11.6 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.6 | 148 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.1 | 95.0 | 120.9 | 241.2 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.4 | 100.0 | 109.3 | 243.8 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.1 | 92.0 | 110.7 | 248.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.3 | 100.0 | 85.8 | 161.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.7 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 16.1 | 22.0 | 88.5 | 101.7 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.1 | 100.0 | 115.2 | 235.4 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.1 | 100.0 | 106.5 | 245.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.0 | 88.0 | 108.8 | 160.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.1 | 148 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.4 | 82.0 | 125.8 | 252.4 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.1 | 100.0 | 121.7 | 245.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.1 | 100.0 | 116.0 | 258.5 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.4 | 98.0 | 109.8 | 266.6 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 10.5 | 21.0 | 92.2 | 124.2 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.8 | 100.0 | 112.4 | 137.4 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.5 | 100.0 | 113.6 | 208.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.0 | 100.0 | 105.6 | 157.8 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 148 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.5 | 100.0 | 124.1 | 252.7 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.6 | 100.0 | 128.5 | 282.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.7 | 100.0 | 121.4 | 260.1 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.3 | 100.0 | 112.8 | 263.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.6 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.7 | 100.0 | 88.4 | 113.9 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.6 | 100.0 | 114.1 | 273.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.6 | 100.0 | 105.3 | 171.0 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.5 | 100.0 | 116.3 | 154.0 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.9 | 148 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 32.9 | 100.0 | 117.4 | 261.8 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.5 | 100.0 | 126.8 | 239.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.9 | 100.0 | 118.4 | 256.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.2 | 100.0 | 99.5 | 243.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 14.5 | 23.0 | 95.4 | 118.3 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.1 | 100.0 | 113.5 | 144.8 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.6 | 100.0 | 102.1 | 224.9 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.5 | 100.0 | 137.0 | 260.9 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 148 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 35.7 | 100.0 | 137.7 | 261.4 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.4 | 100.0 | 132.0 | 278.9 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.5 | 100.0 | 125.8 | 269.4 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.4 | 100.0 | 117.5 | 261.9 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.6 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.7 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.9 | 21.0 | 107.6 | 139.3 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.3 | 100.0 | 108.8 | 166.3 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.3 | 100.0 | 111.5 | 202.7 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.8 | 100.0 | 135.4 | 205.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.6 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 148 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 35.1 | 100.0 | 137.2 | 268.5 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.1 | 100.0 | 133.1 | 270.9 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.5 | 100.0 | 123.7 | 276.6 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.7 | 100.0 | 126.5 | 275.6 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.6 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.5 | 21.0 | 114.5 | 147.2 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.3 | 99.0 | 102.2 | 135.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.9 | 100.0 | 100.5 | 203.7 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.1 | 100.0 | 142.2 | 217.6 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.3 | 148 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 36.3 | 100.0 | 144.5 | 274.1 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.9 | 100.0 | 133.7 | 277.7 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.0 | 100.0 | 123.8 | 268.4 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 100.0 | 132.8 | 279.1 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.6 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.2 | 23.0 | 95.2 | 111.1 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 100.0 | 123.5 | 203.4 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.2 | 100.0 | 117.2 | 257.8 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.1 | 100.0 | 155.9 | 253.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.4 | 148 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 33.5 | 100.0 | 130.8 | 272.5 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.0 | 100.0 | 131.5 | 256.3 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.2 | 100.0 | 122.1 | 279.9 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.3 | 100.0 | 136.5 | 278.6 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.6 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 12.2 | 23.0 | 96.0 | 126.1 | 6398 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.4 | 24.0 | 88.0 | 103.1 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.6 | 100.0 | 112.5 | 247.8 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.6 | 100.0 | 152.9 | 253.9 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.0 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 148 |

