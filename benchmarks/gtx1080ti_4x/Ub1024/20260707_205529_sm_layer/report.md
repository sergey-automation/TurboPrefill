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
- TURBOPREFILL: `0`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_205529/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 1024 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 231.77 | 1.10 | 48.79 | 4.71 |
| ctx_002_000512.txt | 504 | 128 | 663.14 | 0.76 | 52.08 | 3.88 |
| ctx_003_001024.txt | 1017 | 128 | 804.90 | 1.26 | 52.07 | 4.82 |
| ctx_004_002048.txt | 2044 | 128 | 937.98 | 2.18 | 52.49 | 5.50 |
| ctx_005_004096.txt | 4076 | 128 | 991.06 | 4.11 | 51.86 | 7.52 |
| ctx_006_006144.txt | 6142 | 128 | 990.67 | 6.20 | 51.66 | 9.41 |
| ctx_007_008192.txt | 8164 | 106 | 947.46 | 8.62 | 50.24 | 11.57 |
| ctx_008_012288.txt | 12280 | 128 | 851.97 | 14.41 | 49.91 | 17.86 |
| ctx_009_016384.txt | 16373 | 128 | 778.12 | 21.04 | 48.87 | 24.73 |
| ctx_010_024576.txt | 24560 | 128 | 652.65 | 37.63 | 44.89 | 41.85 |
| ctx_011_032768.txt | 32761 | 128 | 561.02 | 58.40 | 42.72 | 63.16 |
| ctx_012_065536.txt | 64423 | 128 | 365.22 | 176.39 | 39.10 | 182.07 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 59.1 | 59.2 | 6159 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 61.7 | 61.7 | 4044 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 57.4 | 57.4 | 4044 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.6 | 74.7 | 5314 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.7 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 15.0 | 21.0 | 87.6 | 155.0 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.1 | 34.0 | 74.3 | 85.5 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.5 | 18.0 | 76.0 | 88.8 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.4 | 38.0 | 124.9 | 191.8 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 148 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.7 | 2.0 | 63.9 | 64.1 | 6353 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.7 | 5.0 | 61.9 | 61.9 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.3 | 5.0 | 62.2 | 62.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 75.4 | 75.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 10.2 | 12.7 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.8 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.5 | 45.0 | 118.5 | 194.3 | 6355 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.4 | 71.0 | 83.8 | 95.0 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.0 | 18.0 | 100.8 | 186.1 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.4 | 57.0 | 127.5 | 156.8 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 10.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 148 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.2 | 1.0 | 75.9 | 76.3 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.2 | 11.0 | 66.9 | 66.9 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.6 | 8.0 | 69.2 | 69.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.8 | 9.0 | 75.9 | 76.0 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 8.9 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.6 | 92.0 | 101.4 | 251.3 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.2 | 38.0 | 97.3 | 183.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.9 | 100.0 | 105.8 | 239.1 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.5 | 100.0 | 112.2 | 158.8 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 148 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 14.1 | 100.0 | 98.4 | 237.3 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.2 | 100.0 | 93.6 | 210.3 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.4 | 48.0 | 97.0 | 248.8 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.8 | 98.0 | 90.0 | 189.3 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.2 | 100.0 | 86.3 | 106.4 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.1 | 65.0 | 114.2 | 236.7 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.9 | 81.0 | 105.6 | 247.0 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.4 | 64.0 | 111.7 | 161.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 148 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.1 | 75.0 | 118.9 | 254.3 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.5 | 99.0 | 116.2 | 274.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.8 | 89.0 | 97.6 | 234.4 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.7 | 81.0 | 98.9 | 248.7 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.9 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.3 | 62.0 | 96.6 | 124.8 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 52.0 | 112.2 | 232.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.7 | 50.0 | 107.3 | 242.7 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.0 | 92.0 | 133.2 | 244.3 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 148 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.3 | 87.0 | 117.9 | 245.4 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.1 | 100.0 | 119.1 | 262.7 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 100.0 | 103.3 | 250.5 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.1 | 99.0 | 91.8 | 254.3 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.2 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.0 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.0 | 22.0 | 98.0 | 118.3 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.0 | 71.0 | 115.4 | 134.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.6 | 99.0 | 116.2 | 230.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.7 | 47.0 | 139.5 | 231.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.4 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.6 | 148 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.5 | 100.0 | 117.3 | 256.8 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.8 | 100.0 | 122.3 | 278.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.4 | 100.0 | 108.8 | 250.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.5 | 100.0 | 99.4 | 248.3 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.7 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.6 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 14.7 | 22.0 | 92.6 | 120.3 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.8 | 93.0 | 112.6 | 229.8 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.5 | 61.0 | 112.1 | 222.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.1 | 100.0 | 133.4 | 265.6 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 148 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.3 | 100.0 | 109.0 | 257.6 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.5 | 100.0 | 119.6 | 282.0 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.4 | 100.0 | 108.3 | 265.6 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.2 | 100.0 | 106.2 | 244.7 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 12.7 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.4 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 15.9 | 23.0 | 95.4 | 119.7 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.2 | 85.0 | 117.3 | 142.0 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.8 | 100.0 | 113.3 | 212.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.1 | 73.0 | 137.4 | 215.3 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.3 | 148 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.9 | 100.0 | 119.0 | 265.9 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.6 | 100.0 | 116.5 | 263.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.0 | 100.0 | 103.3 | 261.4 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 100.0 | 98.1 | 266.1 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.9 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.4 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 14.9 | 22.0 | 99.0 | 124.5 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.9 | 100.0 | 124.9 | 212.7 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.9 | 99.0 | 111.3 | 259.0 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.8 | 100.0 | 136.6 | 253.4 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 148 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.6 | 100.0 | 117.7 | 267.5 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.7 | 100.0 | 122.3 | 267.7 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.2 | 100.0 | 111.9 | 260.5 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.4 | 100.0 | 106.4 | 277.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.4 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 14.8 | 25.0 | 95.4 | 139.9 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.7 | 100.0 | 104.0 | 249.2 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.1 | 100.0 | 116.3 | 278.5 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.6 | 100.0 | 144.3 | 252.3 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.3 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 148 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.1 | 100.0 | 117.5 | 271.5 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.9 | 100.0 | 121.8 | 274.6 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.9 | 100.0 | 109.1 | 276.2 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.3 | 100.0 | 113.2 | 276.7 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.4 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.8 | 23.0 | 87.1 | 110.8 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.9 | 100.0 | 107.6 | 249.9 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.9 | 100.0 | 111.0 | 258.4 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.6 | 100.0 | 144.6 | 258.0 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.8 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 148 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.2 | 100.0 | 115.0 | 281.6 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.0 | 100.0 | 118.8 | 259.5 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.2 | 100.0 | 109.5 | 277.3 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.2 | 100.0 | 119.2 | 276.6 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.5 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.7 | 148 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 13.4 | 26.0 | 89.9 | 117.2 | 6213 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 10.7 | 20.0 | 116.2 | 150.0 | 4098 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.8 | 100.0 | 119.7 | 244.1 | 4098 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.5 | 100.0 | 157.3 | 265.5 | 5368 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.9 | 148 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.1 | 148 |

