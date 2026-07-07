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
- TURBOPREFILL: `0`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_203405/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 512 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 171.16 | 1.49 | 48.82 | 4.83 |
| ctx_002_000512.txt | 504 | 128 | 537.53 | 0.94 | 52.21 | 3.93 |
| ctx_003_001024.txt | 1017 | 128 | 644.84 | 1.58 | 52.46 | 4.88 |
| ctx_004_002048.txt | 2044 | 128 | 879.62 | 2.32 | 52.92 | 5.51 |
| ctx_005_004096.txt | 4076 | 128 | 913.60 | 4.46 | 52.47 | 7.73 |
| ctx_006_006144.txt | 6142 | 128 | 927.85 | 6.62 | 51.72 | 9.78 |
| ctx_007_008192.txt | 8164 | 128 | 881.55 | 9.26 | 50.49 | 12.58 |
| ctx_008_012288.txt | 12280 | 128 | 797.59 | 15.40 | 50.32 | 21.95 |
| ctx_009_016384.txt | 16373 | 128 | 732.38 | 22.36 | 48.42 | 27.50 |
| ctx_010_024576.txt | 24560 | 128 | 619.24 | 39.66 | 47.08 | 43.69 |
| ctx_011_032768.txt | 32761 | 128 | 534.77 | 61.26 | 43.66 | 65.93 |
| ctx_012_065536.txt | 64423 | 128 | 352.91 | 182.55 | 37.84 | 188.27 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.1 | 58.2 | 5437 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 59.4 | 59.5 | 3664 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 55.7 | 55.7 | 3664 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 70.8 | 70.8 | 4624 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.9 | 46.0 | 88.8 | 158.0 | 5494 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.3 | 57.0 | 74.8 | 87.2 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.2 | 34.0 | 66.5 | 80.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.4 | 39.0 | 118.5 | 243.7 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 12.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 2.2 | 5.0 | 99.8 | 201.5 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.8 | 7.0 | 63.9 | 64.0 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.8 | 7.0 | 55.9 | 56.0 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.2 | 6.0 | 72.3 | 72.5 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.6 | 72.0 | 103.7 | 121.3 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.2 | 61.0 | 93.6 | 106.4 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.3 | 77.0 | 87.2 | 143.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.8 | 64.0 | 128.8 | 146.4 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.6 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 10.8 | 64.0 | 72.1 | 73.4 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 7.3 | 29.0 | 78.6 | 105.0 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.3 | 83.0 | 70.0 | 111.5 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 9.3 | 56.0 | 72.3 | 72.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.7 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.8 | 75.0 | 116.0 | 208.7 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 61.0 | 95.3 | 108.8 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.7 | 61.0 | 107.5 | 216.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.2 | 63.0 | 117.8 | 157.7 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.6 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 10.6 | 61.0 | 79.8 | 102.7 | 5494 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.3 | 78.0 | 112.4 | 224.0 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.9 | 79.0 | 72.8 | 73.7 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 2.8 | 12.0 | 136.5 | 268.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.2 | 34.0 | 101.4 | 124.5 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.3 | 18.0 | 103.6 | 171.7 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.0 | 26.0 | 95.5 | 115.1 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.0 | 64.0 | 130.4 | 227.9 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.3 | 79.0 | 105.5 | 259.9 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.1 | 84.0 | 110.2 | 253.4 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 83.0 | 99.6 | 235.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.4 | 58.0 | 72.6 | 85.2 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.1 | 80.0 | 93.3 | 115.1 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.8 | 18.0 | 111.7 | 236.5 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.0 | 73.0 | 92.7 | 113.9 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.7 | 69.0 | 114.4 | 143.7 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.4 | 88.0 | 120.3 | 264.8 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.7 | 96.0 | 111.0 | 268.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.8 | 87.0 | 104.1 | 240.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.6 | 70.0 | 96.9 | 257.2 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.8 | 56.0 | 104.1 | 175.1 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.8 | 40.0 | 103.5 | 119.3 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.4 | 24.0 | 104.2 | 237.6 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.8 | 65.0 | 118.8 | 155.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.0 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.7 | 89.0 | 102.6 | 267.8 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.1 | 100.0 | 126.4 | 265.1 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.2 | 100.0 | 93.9 | 253.3 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.4 | 85.0 | 113.5 | 266.5 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.5 | 96.0 | 105.8 | 224.5 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.2 | 22.0 | 109.0 | 248.6 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.5 | 100.0 | 92.3 | 112.6 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 36.2 | 83.0 | 120.9 | 169.0 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.2 | 93.0 | 120.9 | 262.5 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.2 | 97.0 | 105.6 | 270.5 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.2 | 100.0 | 112.3 | 258.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.9 | 85.0 | 90.4 | 253.7 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.2 | 100.0 | 111.6 | 242.3 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.7 | 100.0 | 123.4 | 258.4 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.7 | 100.0 | 117.8 | 253.9 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.5 | 88.0 | 110.0 | 249.1 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.3 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.7 | 100.0 | 112.1 | 261.0 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.2 | 100.0 | 114.5 | 262.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.0 | 100.0 | 104.0 | 273.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.9 | 79.0 | 108.1 | 263.5 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.1 | 91.0 | 104.3 | 230.8 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 100.0 | 111.7 | 245.5 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.0 | 93.0 | 116.0 | 265.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.4 | 100.0 | 122.7 | 246.3 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.9 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.6 | 100.0 | 114.6 | 272.0 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.6 | 100.0 | 114.7 | 274.6 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.4 | 100.0 | 114.5 | 275.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.7 | 100.0 | 104.9 | 263.6 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.1 | 100.0 | 119.2 | 230.7 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.8 | 100.0 | 106.0 | 137.8 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.9 | 100.0 | 95.2 | 115.0 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.9 | 94.0 | 123.8 | 171.1 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.2 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.1 | 100.0 | 121.6 | 284.2 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.3 | 100.0 | 123.3 | 262.8 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.4 | 100.0 | 112.0 | 279.2 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.3 | 100.0 | 110.1 | 273.3 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.0 | 100.0 | 103.0 | 210.5 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.4 | 100.0 | 110.8 | 230.8 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.6 | 100.0 | 102.2 | 250.3 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.6 | 100.0 | 139.9 | 247.0 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.2 | 100.0 | 118.4 | 275.1 | 5492 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.8 | 100.0 | 120.1 | 293.6 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.2 | 100.0 | 110.5 | 273.3 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.7 | 100.0 | 120.7 | 285.5 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 12.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.3 | 100.0 | 101.3 | 223.5 | 5491 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.5 | 100.0 | 102.5 | 212.9 | 3718 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.3 | 100.0 | 109.9 | 277.8 | 3718 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.3 | 100.0 | 148.5 | 250.4 | 4678 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.4 | 146 |

