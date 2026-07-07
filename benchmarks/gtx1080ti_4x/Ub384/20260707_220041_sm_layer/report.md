# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `384`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `0`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_220041/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 384 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 166.44 | 1.53 | 48.16 | 5.07 |
| ctx_002_000512.txt | 504 | 128 | 411.24 | 1.23 | 52.14 | 4.20 |
| ctx_003_001024.txt | 1017 | 128 | 547.03 | 1.86 | 52.42 | 5.07 |
| ctx_004_002048.txt | 2044 | 128 | 752.54 | 2.72 | 52.48 | 6.04 |
| ctx_005_004096.txt | 4076 | 128 | 837.37 | 4.87 | 51.98 | 8.20 |
| ctx_006_006144.txt | 6142 | 128 | 871.11 | 7.05 | 51.80 | 10.22 |
| ctx_007_008192.txt | 8164 | 106 | 827.82 | 9.86 | 50.80 | 12.74 |
| ctx_008_012288.txt | 12280 | 128 | 757.98 | 16.20 | 50.11 | 19.59 |
| ctx_009_016384.txt | 16373 | 128 | 694.36 | 23.58 | 48.46 | 27.22 |
| ctx_010_024576.txt | 24560 | 128 | 591.61 | 41.51 | 46.14 | 45.55 |
| ctx_011_032768.txt | 32761 | 128 | 514.55 | 63.67 | 44.18 | 68.28 |
| ctx_012_065536.txt | 64423 | 128 | 343.72 | 187.43 | 38.15 | 193.13 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 59.0 | 59.1 | 5659 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 61.5 | 61.5 | 3570 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.4 | 12.0 | 57.7 | 57.8 | 3570 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.6 | 8.0 | 75.1 | 75.2 | 4452 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.4 | 11.9 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 10.0 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.1 | 39.0 | 74.3 | 89.9 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.3 | 44.0 | 80.6 | 97.1 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.3 | 19.0 | 81.1 | 143.7 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.8 | 38.0 | 110.2 | 148.5 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.0 | 10.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 10.1 | 148 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.5 | 46.0 | 62.7 | 66.9 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 12.0 | 41.0 | 70.1 | 74.2 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 11.2 | 24.0 | 91.4 | 177.3 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.5 | 23.0 | 73.3 | 73.4 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.0 | 10.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.0 | 10.2 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.0 | 34.0 | 105.5 | 183.8 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.2 | 60.0 | 100.7 | 115.0 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.2 | 21.0 | 104.0 | 183.1 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.2 | 45.0 | 130.8 | 154.2 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.1 | 10.8 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.7 | 10.2 | 148 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 9.9 | 48.0 | 92.7 | 219.4 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.4 | 42.0 | 79.4 | 84.7 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.4 | 63.0 | 73.3 | 84.2 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 10.7 | 40.0 | 108.9 | 219.8 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.2 | 11.7 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.7 | 10.0 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.2 | 27.0 | 91.8 | 108.2 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.3 | 62.0 | 95.8 | 109.1 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.1 | 48.0 | 111.6 | 241.2 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.5 | 55.0 | 122.5 | 157.1 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.0 | 10.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 11.1 | 148 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 12.9 | 38.0 | 101.4 | 243.6 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.6 | 65.0 | 93.6 | 218.2 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.6 | 56.0 | 92.3 | 244.4 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 5.2 | 36.0 | 90.8 | 225.8 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 10.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.7 | 10.0 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.8 | 33.0 | 99.7 | 138.4 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.8 | 19.0 | 111.6 | 256.9 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.8 | 31.0 | 98.5 | 122.4 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.9 | 41.0 | 120.1 | 153.5 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 10.5 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 12.3 | 148 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 9.5 | 45.0 | 112.6 | 255.5 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.7 | 71.0 | 113.6 | 273.6 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.4 | 72.0 | 106.0 | 270.7 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.2 | 47.0 | 84.5 | 166.0 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.0 | 12.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 11.9 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.9 | 53.0 | 107.7 | 228.0 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.4 | 59.0 | 109.0 | 229.8 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.8 | 53.0 | 112.9 | 251.3 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.2 | 56.0 | 121.3 | 150.3 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 10.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 11.6 | 148 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.2 | 60.0 | 121.4 | 246.9 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.5 | 77.0 | 110.3 | 249.4 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.8 | 78.0 | 108.3 | 274.8 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.8 | 57.0 | 101.5 | 265.5 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 12.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.7 | 10.2 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.6 | 47.0 | 118.4 | 240.6 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.1 | 32.0 | 100.7 | 118.2 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.3 | 19.0 | 110.2 | 205.3 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.5 | 58.0 | 122.2 | 159.3 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 10.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 10.8 | 148 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.0 | 71.0 | 112.9 | 264.2 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.3 | 78.0 | 120.8 | 267.1 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.6 | 83.0 | 95.6 | 260.2 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.5 | 55.0 | 107.1 | 264.0 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.9 | 13.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.7 | 12.3 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.9 | 39.0 | 105.1 | 173.2 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.4 | 54.0 | 105.1 | 153.3 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.7 | 84.0 | 92.2 | 112.3 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.9 | 42.0 | 119.3 | 164.7 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 10.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 10.2 | 148 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.5 | 87.0 | 127.5 | 284.5 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.6 | 90.0 | 118.1 | 260.9 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.3 | 76.0 | 114.6 | 258.1 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.2 | 82.0 | 104.4 | 268.4 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.8 | 12.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 11.9 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.5 | 60.0 | 112.5 | 226.2 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.8 | 60.0 | 116.1 | 131.5 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.8 | 30.0 | 113.4 | 263.7 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.2 | 61.0 | 129.3 | 153.1 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.7 | 11.5 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.5 | 9.8 | 148 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.8 | 83.0 | 127.2 | 272.2 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.3 | 96.0 | 116.3 | 277.4 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.2 | 95.0 | 114.0 | 271.0 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.3 | 93.0 | 100.9 | 260.9 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 12.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.5 | 11.9 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.8 | 63.0 | 110.9 | 244.3 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.3 | 68.0 | 113.1 | 137.7 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.2 | 71.0 | 122.9 | 238.1 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.0 | 88.0 | 134.7 | 235.3 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 10.0 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 11.8 | 148 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.9 | 100.0 | 128.3 | 275.3 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.9 | 100.0 | 122.4 | 284.9 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.4 | 100.0 | 115.4 | 263.5 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.2 | 100.0 | 107.0 | 269.2 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 12.7 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.4 | 12.6 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.9 | 57.0 | 122.0 | 229.6 | 5712 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.4 | 100.0 | 114.7 | 249.2 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.1 | 81.0 | 102.8 | 137.3 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.3 | 100.0 | 132.1 | 174.5 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.4 | 9.8 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 9.7 | 148 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.8 | 100.0 | 120.3 | 270.3 | 5712 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.3 | 100.0 | 118.3 | 274.5 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.9 | 100.0 | 107.6 | 267.5 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.9 | 100.0 | 117.6 | 276.7 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.4 | 12.9 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.2 | 11.7 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.5 | 89.0 | 116.3 | 251.4 | 5712 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.4 | 71.0 | 121.4 | 264.6 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.3 | 47.0 | 114.4 | 227.1 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.7 | 93.0 | 146.6 | 243.1 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 9.8 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 9.5 | 148 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.0 | 100.0 | 122.9 | 285.5 | 5713 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.8 | 100.0 | 122.5 | 287.0 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.9 | 100.0 | 112.9 | 270.3 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.7 | 100.0 | 123.3 | 283.2 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 13.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 12.2 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.9 | 100.0 | 111.3 | 234.3 | 5543 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.8 | 100.0 | 112.8 | 255.0 | 3624 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.2 | 100.0 | 100.2 | 219.4 | 3624 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.9 | 100.0 | 156.8 | 248.4 | 4506 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 11.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.6 | 148 |

