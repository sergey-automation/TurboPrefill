# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `512`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_201251/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 512 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 198.91 | 1.28 | 49.90 | 5.08 |
| ctx_002_000512.txt | 504 | 128 | 605.81 | 0.83 | 52.84 | 3.74 |
| ctx_003_001024.txt | 1017 | 128 | 757.87 | 1.34 | 52.38 | 4.54 |
| ctx_004_002048.txt | 2044 | 128 | 1023.48 | 2.00 | 52.84 | 5.24 |
| ctx_005_004096.txt | 4076 | 128 | 1395.14 | 2.92 | 51.62 | 6.28 |
| ctx_006_006144.txt | 6142 | 13 | 1534.29 | 4.00 | 55.69 | 4.90 |
| ctx_007_008192.txt | 8164 | 128 | 1553.12 | 5.26 | 50.92 | 8.55 |
| ctx_008_012288.txt | 12280 | 128 | 1393.33 | 8.81 | 50.00 | 12.24 |
| ctx_009_016384.txt | 16373 | 128 | 1122.54 | 14.59 | 48.28 | 18.26 |
| ctx_010_024576.txt | 24560 | 128 | 649.06 | 37.84 | 43.93 | 43.15 |
| ctx_011_032768.txt | 32761 | 128 | 864.68 | 37.89 | 43.91 | 48.53 |
| ctx_012_065536.txt | 64423 | 128 | 526.63 | 122.33 | 38.80 | 128.99 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.6 | 58.7 | 5438 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 66.7 | 84.1 | 3664 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.2 | 74.3 | 3664 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.3 | 74.4 | 4624 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.9 | 22.0 | 82.6 | 159.7 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.7 | 20.0 | 76.0 | 85.7 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 12.8 | 19.0 | 77.7 | 101.0 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.1 | 41.0 | 121.5 | 257.7 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.2 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 63.2 | 63.5 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.3 | 7.0 | 67.3 | 67.3 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 66.9 | 66.9 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.7 | 5.0 | 74.0 | 74.0 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.1 | 12.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.3 | 33.0 | 102.5 | 122.4 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.6 | 83.0 | 103.7 | 160.6 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.3 | 81.0 | 93.3 | 112.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.6 | 41.0 | 135.1 | 265.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.8 | 2.0 | 108.4 | 242.0 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.0 | 40.0 | 77.2 | 80.7 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 6.8 | 26.0 | 73.9 | 82.1 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 104.8 | 225.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.7 | 66.0 | 116.3 | 255.3 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.9 | 56.0 | 94.2 | 113.1 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 43.0 | 110.5 | 249.3 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.6 | 44.0 | 112.4 | 139.1 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 30.3 | 75.0 | 94.4 | 211.7 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.7 | 81.0 | 126.1 | 262.4 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.9 | 77.0 | 75.9 | 76.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 9.7 | 54.0 | 75.5 | 77.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.4 | 78.0 | 93.1 | 113.7 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.8 | 63.0 | 121.0 | 234.3 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.3 | 74.0 | 97.2 | 121.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.2 | 42.0 | 118.2 | 158.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.7 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.0 | 80.0 | 125.0 | 250.3 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.5 | 78.0 | 132.8 | 263.1 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.2 | 80.0 | 113.3 | 262.1 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.0 | 57.0 | 95.8 | 251.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.2 | 76.0 | 102.1 | 245.8 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.5 | 83.0 | 104.8 | 133.5 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.8 | 69.0 | 102.1 | 244.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.7 | 58.0 | 121.3 | 261.5 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 39.1 | 80.0 | 127.7 | 251.8 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.2 | 83.0 | 141.7 | 259.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.1 | 89.0 | 109.6 | 259.7 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.1 | 66.0 | 107.0 | 261.2 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 28.2 | 58.0 | 132.7 | 260.1 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.8 | 63.0 | 100.0 | 128.2 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.0 | 69.0 | 139.2 | 268.3 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 49.0 | 81.0 | 100.0 | 162.3 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.6 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 45.5 | 90.0 | 132.4 | 258.9 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.0 | 80.0 | 146.9 | 274.8 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.3 | 84.0 | 134.2 | 255.4 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.3 | 81.0 | 127.9 | 253.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 16.3 | 22.0 | 117.4 | 246.3 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.1 | 77.0 | 121.0 | 158.7 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.7 | 21.0 | 114.3 | 244.7 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.2 | 42.0 | 122.1 | 157.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.4 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 39.9 | 96.0 | 134.9 | 248.5 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.3 | 96.0 | 140.8 | 263.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.4 | 83.0 | 126.5 | 258.7 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.0 | 88.0 | 110.1 | 264.1 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.6 | 50.0 | 106.7 | 134.3 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.0 | 78.0 | 116.5 | 132.7 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.6 | 34.0 | 106.3 | 228.6 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.4 | 41.0 | 137.2 | 225.0 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 38.1 | 100.0 | 139.2 | 267.4 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.7 | 100.0 | 144.2 | 273.1 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.2 | 100.0 | 144.6 | 266.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.1 | 98.0 | 130.2 | 267.7 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.3 | 90.0 | 124.9 | 208.6 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.8 | 100.0 | 122.0 | 248.6 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.0 | 100.0 | 116.6 | 267.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.1 | 40.0 | 135.5 | 228.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.2 | 100.0 | 133.6 | 272.1 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.0 | 100.0 | 136.8 | 274.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.6 | 100.0 | 128.1 | 272.3 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.0 | 100.0 | 119.7 | 265.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 15.7 | 100.0 | 107.5 | 246.8 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.0 | 100.0 | 96.5 | 133.6 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.4 | 100.0 | 99.6 | 231.1 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.8 | 100.0 | 129.4 | 225.4 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.6 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 35.6 | 100.0 | 145.2 | 275.8 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.8 | 100.0 | 126.8 | 275.4 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.8 | 100.0 | 114.4 | 256.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.0 | 100.0 | 122.7 | 283.1 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.6 | 100.0 | 119.9 | 251.8 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.6 | 100.0 | 117.5 | 220.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.1 | 100.0 | 109.7 | 235.0 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.3 | 100.0 | 137.6 | 256.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.4 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 37.5 | 100.0 | 147.3 | 286.5 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.6 | 100.0 | 137.6 | 283.1 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.2 | 100.0 | 127.4 | 279.0 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.3 | 100.0 | 142.1 | 287.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.5 | 100.0 | 117.9 | 245.6 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.1 | 100.0 | 119.9 | 215.0 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.4 | 100.0 | 106.0 | 264.5 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.3 | 100.0 | 148.1 | 252.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.4 | 8.7 | 146 |

