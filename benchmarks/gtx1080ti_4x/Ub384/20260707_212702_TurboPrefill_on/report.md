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
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_212702/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 384 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 236.24 | 1.08 | 50.99 | 4.53 |
| ctx_002_000512.txt | 504 | 128 | 525.60 | 0.96 | 51.00 | 4.20 |
| ctx_003_001024.txt | 1017 | 128 | 736.52 | 1.38 | 49.54 | 4.95 |
| ctx_004_002048.txt | 2044 | 128 | 1217.22 | 1.68 | 52.94 | 4.89 |
| ctx_005_004096.txt | 4076 | 128 | 1479.19 | 2.76 | 52.39 | 5.98 |
| ctx_006_006144.txt | 6142 | 128 | 1576.02 | 3.90 | 51.27 | 7.05 |
| ctx_007_008192.txt | 8164 | 43 | 1589.64 | 5.14 | 51.92 | 6.77 |
| ctx_008_012288.txt | 12280 | 128 | 1390.07 | 8.83 | 49.75 | 12.18 |
| ctx_009_016384.txt | 16373 | 128 | 1320.07 | 12.40 | 48.93 | 15.99 |
| ctx_010_024576.txt | 24560 | 128 | 1076.89 | 22.81 | 46.59 | 26.84 |
| ctx_011_032768.txt | 32761 | 128 | 914.96 | 35.81 | 43.74 | 40.42 |
| ctx_012_065536.txt | 64423 | 128 | 583.23 | 110.46 | 37.74 | 116.14 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 71.5 | 71.6 | 5441 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 84.2 | 84.2 | 3568 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.9 | 75.0 | 3568 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 73.3 | 73.4 | 4450 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.5 | 49.0 | 101.0 | 124.0 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.8 | 49.0 | 97.3 | 114.1 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.1 | 18.0 | 114.0 | 266.1 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.0 | 41.0 | 116.5 | 148.4 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.4 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 11.0 | 44.0 | 61.5 | 66.3 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 10.0 | 40.0 | 62.5 | 62.8 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 3.5 | 14.0 | 59.9 | 66.4 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.0 | 4.0 | 112.5 | 227.8 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 15.0 | 21.0 | 101.2 | 203.9 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 54.0 | 78.8 | 92.2 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.0 | 20.0 | 82.5 | 151.9 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.7 | 56.0 | 112.8 | 152.6 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 9.8 | 48.0 | 71.4 | 71.8 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.8 | 44.0 | 70.3 | 82.5 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 85.4 | 177.4 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.8 | 9.0 | 74.6 | 74.7 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 16.9 | 51.0 | 111.8 | 204.3 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.4 | 49.0 | 117.6 | 223.9 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.2 | 31.0 | 90.1 | 109.5 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.9 | 44.0 | 119.2 | 151.6 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.3 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.0 | 83.0 | 133.4 | 254.9 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.7 | 69.0 | 148.0 | 278.3 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.7 | 84.0 | 133.7 | 262.8 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.0 | 50.0 | 94.0 | 167.7 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 10.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.7 | 38.0 | 103.5 | 128.8 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.3 | 18.0 | 117.5 | 218.1 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.0 | 59.0 | 104.4 | 197.5 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.9 | 41.0 | 113.0 | 159.3 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 40.6 | 82.0 | 145.3 | 260.6 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.3 | 74.0 | 161.3 | 268.2 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.3 | 80.0 | 123.8 | 243.8 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.2 | 60.0 | 120.7 | 264.6 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.0 | 67.0 | 112.6 | 236.7 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.5 | 72.0 | 108.0 | 133.5 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.3 | 53.0 | 111.2 | 251.5 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.7 | 47.0 | 115.0 | 140.2 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 48.6 | 91.0 | 163.4 | 271.9 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.6 | 76.0 | 145.8 | 281.1 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.9 | 74.0 | 142.6 | 262.6 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.4 | 63.0 | 117.5 | 252.0 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 16.1 | 22.0 | 109.4 | 228.2 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.7 | 64.0 | 101.0 | 117.1 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.2 | 19.0 | 108.6 | 270.6 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.6 | 63.0 | 120.6 | 162.4 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.6 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 45.4 | 75.0 | 152.3 | 261.9 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 48.1 | 77.0 | 144.2 | 282.3 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.2 | 73.0 | 133.8 | 260.4 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.8 | 56.0 | 129.2 | 266.9 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.0 | 54.0 | 93.1 | 115.4 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.0 | 56.0 | 108.1 | 130.8 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.2 | 41.0 | 113.8 | 207.9 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.0 | 53.0 | 108.2 | 151.9 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 45.6 | 92.0 | 163.1 | 260.2 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.8 | 88.0 | 146.3 | 257.5 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.9 | 79.0 | 134.1 | 262.7 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.6 | 65.0 | 117.6 | 265.2 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.0 | 82.0 | 111.5 | 207.7 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.9 | 49.0 | 133.6 | 242.0 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.2 | 78.0 | 101.0 | 119.0 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.1 | 61.0 | 139.0 | 245.0 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.6 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 48.3 | 91.0 | 128.8 | 280.9 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 55.8 | 98.0 | 126.9 | 264.5 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.3 | 95.0 | 119.0 | 275.9 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.7 | 78.0 | 114.4 | 275.5 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.7 | 84.0 | 111.3 | 181.4 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.5 | 71.0 | 118.7 | 143.9 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.5 | 29.0 | 113.2 | 245.4 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.3 | 68.0 | 131.8 | 166.8 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 40.4 | 99.0 | 164.1 | 276.2 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 52.4 | 100.0 | 149.4 | 293.0 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.3 | 92.0 | 133.1 | 268.3 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.4 | 80.0 | 129.2 | 266.4 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.6 | 83.0 | 132.6 | 252.9 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.3 | 84.0 | 130.4 | 223.9 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.3 | 91.0 | 116.2 | 249.3 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.7 | 41.0 | 155.3 | 216.0 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.6 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 46.4 | 100.0 | 164.3 | 283.7 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.9 | 100.0 | 141.7 | 280.7 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 47.4 | 100.0 | 128.6 | 267.2 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.3 | 100.0 | 136.9 | 281.5 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.2 | 37.0 | 118.6 | 254.1 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.8 | 100.0 | 121.0 | 241.4 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.5 | 93.0 | 105.8 | 216.7 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.4 | 88.0 | 166.8 | 225.8 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 43.3 | 100.0 | 155.8 | 291.0 | 5496 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.3 | 100.0 | 141.9 | 280.6 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.2 | 100.0 | 130.0 | 279.3 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.5 | 100.0 | 145.5 | 298.9 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.8 | 100.0 | 107.1 | 198.5 | 5495 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.7 | 100.0 | 115.3 | 247.9 | 3622 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.7 | 100.0 | 113.9 | 228.5 | 3622 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.7 | 100.0 | 152.0 | 255.5 | 4504 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.9 | 146 |

