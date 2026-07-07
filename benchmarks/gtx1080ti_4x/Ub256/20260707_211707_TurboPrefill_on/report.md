# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `256`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_211707/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 256 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 190.90 | 1.34 | 50.81 | 4.64 |
| ctx_002_000512.txt | 504 | 128 | 428.90 | 1.18 | 51.19 | 4.33 |
| ctx_003_001024.txt | 1017 | 128 | 574.72 | 1.77 | 50.98 | 4.97 |
| ctx_004_002048.txt | 2044 | 128 | 1111.09 | 1.84 | 52.60 | 5.12 |
| ctx_005_004096.txt | 4076 | 128 | 1386.38 | 2.94 | 52.58 | 6.48 |
| ctx_006_006144.txt | 6142 | 128 | 1492.22 | 4.12 | 52.04 | 7.21 |
| ctx_007_008192.txt | 8164 | 21 | 1459.19 | 5.59 | 53.57 | 6.78 |
| ctx_008_012288.txt | 12280 | 128 | 1339.16 | 9.17 | 50.23 | 12.52 |
| ctx_009_016384.txt | 16373 | 128 | 1078.02 | 15.19 | 48.28 | 19.14 |
| ctx_010_024576.txt | 24560 | 128 | 1039.44 | 23.63 | 46.32 | 30.59 |
| ctx_011_032768.txt | 32761 | 97 | 891.88 | 36.73 | 45.34 | 40.70 |
| ctx_012_065536.txt | 64423 | 128 | 551.52 | 116.81 | 37.46 | 122.62 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.8 | 58.9 | 5081 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 84.3 | 84.4 | 3476 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.3 | 74.4 | 3476 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.0 | 74.2 | 4280 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.6 | 57.0 | 78.2 | 99.0 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.2 | 42.0 | 96.7 | 116.2 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.1 | 48.0 | 103.4 | 203.4 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.2 | 41.0 | 111.6 | 151.6 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.8 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 4.2 | 17.0 | 65.8 | 72.7 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 83.6 | 145.5 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 58.1 | 58.1 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.9 | 75.1 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 10.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.4 | 23.0 | 88.8 | 181.7 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 55.0 | 81.7 | 92.8 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.9 | 52.0 | 92.3 | 113.8 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 41.0 | 118.1 | 154.4 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.8 | 91.0 | 97.0 | 182.4 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.5 | 79.0 | 71.2 | 79.1 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 6.8 | 34.0 | 99.1 | 227.3 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.7 | 23.0 | 102.7 | 241.2 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 15.1 | 21.0 | 110.2 | 248.2 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.7 | 49.0 | 104.6 | 127.4 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.5 | 52.0 | 96.5 | 119.8 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.6 | 41.0 | 125.5 | 206.4 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.7 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.6 | 84.0 | 112.9 | 251.2 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.9 | 75.0 | 119.7 | 182.9 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.1 | 89.0 | 104.0 | 235.4 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.0 | 45.0 | 98.8 | 227.0 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.5 | 51.0 | 97.6 | 121.2 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.9 | 50.0 | 111.1 | 269.6 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.1 | 52.0 | 98.8 | 121.2 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.1 | 41.0 | 121.0 | 181.7 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 41.4 | 90.0 | 137.0 | 244.0 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.0 | 80.0 | 142.1 | 252.9 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.5 | 75.0 | 143.1 | 257.1 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.3 | 53.0 | 111.6 | 222.0 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.2 | 57.0 | 112.2 | 251.1 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.0 | 37.0 | 121.9 | 247.3 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.6 | 55.0 | 97.8 | 115.5 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.8 | 60.0 | 131.9 | 248.7 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 53.6 | 91.0 | 148.4 | 254.4 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.3 | 78.0 | 129.2 | 259.7 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.6 | 74.0 | 127.8 | 242.1 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.8 | 57.0 | 119.8 | 257.8 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.4 | 62.0 | 97.9 | 122.4 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.8 | 19.0 | 111.5 | 133.4 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.2 | 59.0 | 107.0 | 212.4 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.3 | 46.0 | 118.7 | 137.3 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 10.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 52.8 | 88.0 | 144.6 | 250.1 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.6 | 82.0 | 133.2 | 249.4 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.0 | 72.0 | 126.9 | 258.0 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.0 | 81.0 | 112.0 | 255.8 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 5.8 | 21.0 | 107.2 | 174.2 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.0 | 65.0 | 99.9 | 116.6 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.0 | 65.0 | 129.3 | 259.4 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.5 | 51.0 | 132.5 | 251.2 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.5 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 53.2 | 88.0 | 182.7 | 261.7 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.2 | 79.0 | 153.7 | 272.9 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 49.8 | 74.0 | 139.3 | 266.2 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.0 | 75.0 | 126.2 | 257.3 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 14.8 | 22.0 | 121.4 | 247.7 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.8 | 77.0 | 118.7 | 145.8 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.5 | 78.0 | 114.9 | 252.7 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.8 | 60.0 | 135.2 | 170.7 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.4 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 47.2 | 95.0 | 162.0 | 265.6 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 45.2 | 84.0 | 149.5 | 269.4 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.0 | 77.0 | 137.2 | 261.0 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.3 | 76.0 | 138.1 | 277.6 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.4 | 52.0 | 121.4 | 233.9 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.3 | 67.0 | 117.6 | 146.6 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.9 | 44.0 | 112.0 | 243.5 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.9 | 71.0 | 119.7 | 175.0 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 45.0 | 90.0 | 171.8 | 279.7 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.3 | 97.0 | 154.4 | 270.6 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.9 | 80.0 | 138.8 | 266.6 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.8 | 73.0 | 134.8 | 270.5 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.5 | 64.0 | 161.4 | 242.0 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.2 | 94.0 | 148.8 | 250.5 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.5 | 79.0 | 134.6 | 256.0 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 45.0 | 93.0 | 137.3 | 230.3 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.8 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 50.9 | 100.0 | 165.3 | 284.5 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.1 | 99.0 | 149.7 | 286.4 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.0 | 91.0 | 142.9 | 264.0 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.9 | 100.0 | 147.3 | 274.4 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.3 | 62.0 | 151.0 | 249.0 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.0 | 100.0 | 106.1 | 136.9 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.4 | 45.0 | 102.5 | 134.0 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.2 | 41.0 | 173.9 | 273.7 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 42.9 | 100.0 | 158.8 | 294.0 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.8 | 100.0 | 140.0 | 272.3 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.1 | 100.0 | 133.0 | 265.2 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.4 | 100.0 | 145.7 | 275.9 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.3 | 85.0 | 125.9 | 227.3 | 5135 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.1 | 100.0 | 105.8 | 218.5 | 3530 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.2 | 100.0 | 100.1 | 137.0 | 3530 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.9 | 82.0 | 147.9 | 232.3 | 4334 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.6 | 146 |

