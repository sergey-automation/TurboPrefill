# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `32`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_194621/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 32 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 202.24 | 1.26 | 49.68 | 4.67 |
| ctx_002_000512.txt | 504 | 8 | 585.32 | 0.86 | 60.37 | 1.53 |
| ctx_003_001024.txt | 1017 | 94 | 695.34 | 1.46 | 50.04 | 4.06 |
| ctx_004_002048.txt | 2044 | 128 | 826.81 | 2.47 | 53.32 | 5.65 |
| ctx_005_004096.txt | 4076 | 16 | 889.74 | 4.58 | 55.80 | 5.72 |
| ctx_006_006144.txt | 6142 | 30 | 836.49 | 7.34 | 51.27 | 8.58 |
| ctx_007_008192.txt | 8164 | 21 | 826.05 | 9.88 | 50.98 | 11.12 |
| ctx_008_012288.txt | 12280 | 16 | 753.38 | 16.30 | 50.01 | 17.53 |
| ctx_009_016384.txt | 16373 | 1 | 709.40 | 23.08 | 1000000.00 | 24.05 |
| ctx_010_024576.txt | 24560 | 128 | 615.17 | 39.92 | 42.92 | 44.17 |
| ctx_011_032768.txt | 32761 | 71 | 612.42 | 53.49 | 42.33 | 56.84 |
| ctx_012_065536.txt | 64423 | 128 | 457.15 | 140.92 | 37.02 | 146.67 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 59.0 | 59.1 | 4816 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 62.3 | 62.3 | 3312 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 58.1 | 58.2 | 3312 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.4 | 74.5 | 3982 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.7 | 61.0 | 95.4 | 147.5 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 51.0 | 85.5 | 144.6 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 68.0 | 76.2 | 85.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.2 | 41.0 | 114.8 | 142.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.7 | 53.0 | 132.2 | 253.3 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.0 | 6.0 | 96.3 | 153.7 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 4.0 | 6.0 | 91.0 | 147.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.7 | 5.0 | 116.4 | 198.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 43.0 | 90.0 | 135.2 | 248.3 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.0 | 82.0 | 118.2 | 173.0 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.0 | 76.0 | 116.8 | 188.2 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.7 | 44.0 | 119.8 | 189.9 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.9 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.4 | 86.0 | 144.8 | 251.9 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 70.0 | 135.4 | 235.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.0 | 73.0 | 136.2 | 238.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 11.8 | 49.0 | 115.3 | 207.0 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 33.3 | 90.0 | 109.8 | 236.1 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.3 | 74.0 | 120.9 | 198.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.2 | 68.0 | 122.2 | 213.8 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.7 | 47.0 | 140.0 | 175.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 10.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.4 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 54.0 | 91.0 | 189.0 | 253.4 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 46.7 | 79.0 | 174.9 | 254.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.7 | 74.0 | 138.8 | 239.6 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.2 | 46.0 | 126.4 | 177.2 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.7 | 90.0 | 120.1 | 209.0 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.2 | 73.0 | 124.3 | 229.7 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.8 | 66.0 | 114.0 | 238.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.9 | 46.0 | 122.4 | 161.5 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 68.4 | 92.0 | 209.7 | 252.7 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.2 | 76.0 | 191.0 | 254.5 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 48.4 | 70.0 | 154.9 | 217.3 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.9 | 45.0 | 128.1 | 198.2 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 55.5 | 88.0 | 139.6 | 260.2 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.2 | 61.0 | 135.7 | 197.1 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.2 | 58.0 | 112.0 | 138.2 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.0 | 44.0 | 119.6 | 147.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 10.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.3 | 8.5 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 76.4 | 91.0 | 213.7 | 252.7 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.1 | 69.0 | 191.1 | 241.9 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.4 | 64.0 | 172.5 | 227.6 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.0 | 46.0 | 146.0 | 210.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 39.8 | 87.0 | 140.9 | 206.6 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.5 | 66.0 | 169.6 | 234.3 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.5 | 54.0 | 118.1 | 183.9 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.5 | 44.0 | 137.8 | 200.7 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 76.7 | 91.0 | 215.1 | 262.2 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 57.1 | 72.0 | 197.0 | 264.7 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 52.6 | 66.0 | 161.6 | 243.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.7 | 48.0 | 146.2 | 210.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 45.6 | 86.0 | 179.2 | 259.9 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.8 | 74.0 | 108.4 | 144.7 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.2 | 60.0 | 152.9 | 219.9 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.0 | 49.0 | 153.5 | 190.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.6 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 79.1 | 92.0 | 194.1 | 247.4 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 57.4 | 85.0 | 183.7 | 263.3 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.1 | 70.0 | 168.2 | 232.2 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.4 | 47.0 | 156.2 | 230.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 12.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 52.4 | 89.0 | 160.5 | 208.5 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.8 | 66.0 | 110.4 | 138.0 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.0 | 54.0 | 123.3 | 199.1 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.0 | 47.0 | 152.0 | 222.6 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 80.2 | 93.0 | 193.6 | 224.1 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.6 | 70.0 | 168.2 | 259.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 49.8 | 62.0 | 158.4 | 225.9 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.2 | 57.0 | 178.3 | 268.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 63.0 | 88.0 | 183.5 | 204.4 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 59.0 | 69.0 | 147.8 | 168.1 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.7 | 54.0 | 210.5 | 221.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.3 | 53.0 | 180.9 | 239.4 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.7 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 80.0 | 93.0 | 212.4 | 245.0 | 4826 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.4 | 73.0 | 160.7 | 251.3 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 49.5 | 61.0 | 157.0 | 232.2 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 42.1 | 67.0 | 172.0 | 281.6 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 34.5 | 83.0 | 144.6 | 228.1 | 4825 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.3 | 60.0 | 136.9 | 250.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.7 | 54.0 | 121.0 | 188.2 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.9 | 51.0 | 156.8 | 220.0 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.8 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 77.3 | 92.0 | 202.1 | 250.3 | 4825 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.7 | 80.0 | 171.4 | 269.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 52.2 | 68.0 | 163.5 | 238.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.2 | 78.0 | 178.0 | 281.6 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 41.9 | 86.0 | 141.4 | 184.2 | 4823 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 69.0 | 155.2 | 243.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.5 | 62.0 | 160.1 | 225.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.4 | 60.0 | 178.9 | 240.9 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 70.0 | 92.0 | 195.6 | 266.3 | 4823 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.4 | 74.0 | 163.7 | 273.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 50.0 | 85.0 | 159.0 | 244.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 45.9 | 100.0 | 176.7 | 289.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 34.0 | 79.0 | 132.5 | 239.7 | 4823 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.6 | 67.0 | 120.4 | 170.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.6 | 67.0 | 113.4 | 221.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 39.4 | 67.0 | 140.9 | 188.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.4 | 9.9 | 146 |

