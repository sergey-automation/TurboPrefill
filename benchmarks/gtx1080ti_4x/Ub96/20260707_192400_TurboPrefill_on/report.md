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
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_192400/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 96 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 155.31 | 1.64 | 50.07 | 5.17 |
| ctx_002_000512.txt | 504 | 128 | 546.27 | 0.92 | 53.16 | 4.22 |
| ctx_003_001024.txt | 1017 | 128 | 708.71 | 1.43 | 52.73 | 4.76 |
| ctx_004_002048.txt | 2044 | 128 | 1060.64 | 1.93 | 52.32 | 5.90 |
| ctx_005_004096.txt | 4076 | 128 | 1141.61 | 3.57 | 52.60 | 6.75 |
| ctx_006_006144.txt | 6142 | 128 | 1173.02 | 5.24 | 50.93 | 8.36 |
| ctx_007_008192.txt | 8164 | 17 | 1232.67 | 6.62 | 54.18 | 7.76 |
| ctx_008_012288.txt | 12280 | 20 | 1082.56 | 11.34 | 52.04 | 12.54 |
| ctx_009_016384.txt | 16373 | 128 | 1011.27 | 16.19 | 48.32 | 19.83 |
| ctx_010_024576.txt | 24560 | 20 | 856.60 | 28.67 | 47.17 | 30.36 |
| ctx_011_032768.txt | 32761 | 128 | 755.71 | 43.35 | 43.19 | 47.99 |
| ctx_012_065536.txt | 64423 | 128 | 534.80 | 120.46 | 39.17 | 126.01 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.0 | 58.0 | 5059 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 82.1 | 82.2 | 3358 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 73.4 | 73.5 | 3358 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 72.7 | 72.9 | 4066 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 9.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.8 | 38.0 | 87.2 | 150.7 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.8 | 30.0 | 110.7 | 229.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.4 | 30.0 | 91.6 | 106.1 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.6 | 41.0 | 108.2 | 137.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.2 | 58.4 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.5 | 6.0 | 80.6 | 80.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.5 | 6.0 | 73.8 | 73.9 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.2 | 5.0 | 73.3 | 73.4 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.2 | 47.0 | 109.1 | 188.4 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.3 | 29.0 | 118.9 | 244.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 50.0 | 110.5 | 246.4 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.5 | 53.0 | 115.2 | 148.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 10.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.2 | 87.0 | 139.1 | 248.2 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.6 | 73.0 | 91.3 | 146.4 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.8 | 44.0 | 68.0 | 112.3 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 9.4 | 47.0 | 76.0 | 85.1 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.7 | 68.0 | 95.5 | 120.6 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.7 | 78.0 | 107.3 | 125.3 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 76.0 | 115.0 | 239.0 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.8 | 53.0 | 118.6 | 148.5 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 9.9 | 68.0 | 96.9 | 239.9 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 12.1 | 75.0 | 106.9 | 245.4 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 9.9 | 59.0 | 93.4 | 213.1 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 3.6 | 20.0 | 78.3 | 103.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.1 | 11.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 38.0 | 86.0 | 129.1 | 246.5 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.4 | 75.0 | 128.7 | 213.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.9 | 79.0 | 114.7 | 210.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.8 | 55.0 | 134.1 | 223.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 11.9 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 64.1 | 91.0 | 201.0 | 258.2 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 48.6 | 73.0 | 153.7 | 253.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.6 | 73.0 | 130.5 | 226.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.6 | 53.0 | 104.1 | 185.5 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 16.9 | 22.0 | 104.0 | 126.7 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.2 | 53.0 | 122.3 | 251.5 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.9 | 63.0 | 94.6 | 117.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.0 | 60.0 | 113.8 | 152.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 12.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.3 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 67.3 | 87.0 | 200.5 | 254.9 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 59.1 | 74.0 | 174.3 | 261.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 52.9 | 74.0 | 145.3 | 230.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.3 | 53.0 | 119.5 | 225.7 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.0 | 37.0 | 100.0 | 124.6 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.5 | 31.0 | 114.0 | 145.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 41.0 | 118.1 | 217.0 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.1 | 46.0 | 118.5 | 153.7 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 66.4 | 85.0 | 195.1 | 252.2 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 60.6 | 84.0 | 154.7 | 268.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 58.1 | 85.0 | 136.2 | 236.6 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.2 | 55.0 | 130.5 | 226.8 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 42.8 | 75.0 | 151.4 | 257.2 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.2 | 69.0 | 155.1 | 264.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.0 | 62.0 | 122.8 | 205.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.5 | 62.0 | 103.1 | 129.1 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 68.7 | 86.0 | 203.2 | 265.8 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 58.0 | 74.0 | 179.6 | 260.1 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.1 | 72.0 | 160.6 | 242.0 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.1 | 54.0 | 143.1 | 233.4 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 32.2 | 83.0 | 156.5 | 225.3 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.8 | 67.0 | 137.9 | 244.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.0 | 70.0 | 120.0 | 233.1 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 58.0 | 124.7 | 207.8 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 10.9 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 69.1 | 94.0 | 191.2 | 268.9 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 58.3 | 78.0 | 156.4 | 272.1 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 55.2 | 73.0 | 145.8 | 249.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.3 | 60.0 | 149.3 | 238.3 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.6 | 75.0 | 125.6 | 198.3 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.1 | 74.0 | 124.9 | 238.8 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.8 | 69.0 | 124.5 | 235.7 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.3 | 45.0 | 157.2 | 243.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 11.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.7 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 67.6 | 91.0 | 186.2 | 259.1 | 5069 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.8 | 76.0 | 151.0 | 277.3 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 52.7 | 75.0 | 141.3 | 245.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.4 | 60.0 | 159.5 | 259.9 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 33.8 | 57.0 | 152.0 | 235.4 | 5064 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.7 | 61.0 | 141.3 | 231.6 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.5 | 52.0 | 125.2 | 222.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 45.2 | 72.0 | 154.9 | 211.6 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.2 | 10.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 64.1 | 89.0 | 187.3 | 299.2 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.8 | 78.0 | 156.8 | 273.7 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.2 | 75.0 | 150.4 | 246.8 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.9 | 95.0 | 155.7 | 282.7 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 12.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.1 | 67.0 | 150.4 | 229.7 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.7 | 55.0 | 144.5 | 265.0 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.3 | 82.0 | 128.6 | 244.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.2 | 70.0 | 155.4 | 288.2 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 57.5 | 93.0 | 177.6 | 290.1 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.4 | 100.0 | 147.5 | 277.4 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.0 | 86.0 | 136.6 | 255.2 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 45.6 | 100.0 | 151.8 | 290.8 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.9 | 69.0 | 136.1 | 189.6 | 4884 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.4 | 74.0 | 129.7 | 243.9 | 3410 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.9 | 87.0 | 112.9 | 238.3 | 3410 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.9 | 83.0 | 171.3 | 289.1 | 4118 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.8 | 146 |

