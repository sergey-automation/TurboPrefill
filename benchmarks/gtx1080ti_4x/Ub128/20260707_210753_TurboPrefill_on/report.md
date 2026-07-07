# llama-server context benchmark report

## Test header

- MODEL: `/run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf`
- NGL: `99`
- CTX_SIZE: `66096`
- N_GEN: `128`
- BATCH: `8192`
- UBATCH: `128`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_210753/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 128 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 149.80 | 1.70 | 47.63 | 5.77 |
| ctx_002_000512.txt | 504 | 128 | 375.18 | 1.34 | 52.64 | 4.27 |
| ctx_003_001024.txt | 1017 | 128 | 669.63 | 1.52 | 50.69 | 5.15 |
| ctx_004_002048.txt | 2044 | 128 | 1054.83 | 1.94 | 52.83 | 5.20 |
| ctx_005_004096.txt | 4076 | 10 | 1215.65 | 3.35 | 57.60 | 4.44 |
| ctx_006_006144.txt | 6142 | 37 | 1286.57 | 4.77 | 52.56 | 6.09 |
| ctx_007_008192.txt | 8164 | 29 | 1271.84 | 6.42 | 52.90 | 7.75 |
| ctx_008_012288.txt | 12280 | 13 | 1165.56 | 10.54 | 53.80 | 11.61 |
| ctx_009_016384.txt | 16373 | 95 | 1087.81 | 15.05 | 48.91 | 17.99 |
| ctx_010_024576.txt | 24560 | 128 | 915.76 | 26.82 | 45.25 | 30.91 |
| ctx_011_032768.txt | 32761 | 128 | 806.31 | 40.63 | 42.83 | 45.32 |
| ctx_012_065536.txt | 64423 | 128 | 553.95 | 116.30 | 38.75 | 121.88 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 58.5 | 58.7 | 4901 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 61.3 | 61.5 | 3382 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 57.1 | 57.2 | 3382 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 74.0 | 74.1 | 4110 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 18.5 | 42.0 | 72.6 | 89.2 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.7 | 40.0 | 75.6 | 90.5 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 11.7 | 18.0 | 77.4 | 133.1 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.0 | 38.0 | 107.5 | 152.7 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.4 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 5.0 | 13.0 | 84.9 | 163.8 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 13.4 | 50.0 | 104.8 | 245.3 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.6 | 80.0 | 61.2 | 66.6 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 5.8 | 24.0 | 95.6 | 178.1 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 16.8 | 22.0 | 105.6 | 155.1 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.1 | 36.0 | 106.0 | 121.9 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.6 | 39.0 | 82.5 | 93.8 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.9 | 41.0 | 130.7 | 160.3 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 100.3 | 222.5 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.6 | 6.0 | 109.8 | 224.7 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.6 | 5.0 | 63.3 | 63.3 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 1.4 | 7.0 | 75.4 | 75.6 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.7 | 91.0 | 100.9 | 207.4 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.9 | 80.0 | 116.2 | 233.6 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.6 | 84.0 | 99.6 | 212.5 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.3 | 41.0 | 120.5 | 219.8 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.9 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 46.6 | 87.0 | 165.1 | 254.2 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.7 | 73.0 | 154.4 | 265.2 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.7 | 73.0 | 150.3 | 256.2 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.3 | 47.0 | 109.0 | 232.2 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.7 | 46.0 | 110.2 | 195.0 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.2 | 36.0 | 107.0 | 130.6 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.7 | 35.0 | 100.3 | 142.4 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.5 | 43.0 | 124.7 | 161.2 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.4 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 55.8 | 92.0 | 177.9 | 253.3 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 48.0 | 81.0 | 157.6 | 254.7 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.4 | 70.0 | 144.3 | 251.7 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.8 | 47.0 | 119.6 | 228.1 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 12.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.2 | 41.0 | 86.1 | 116.5 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.0 | 37.0 | 86.3 | 88.7 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.2 | 55.0 | 77.4 | 77.6 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 29.0 | 56.0 | 84.0 | 99.5 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.9 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 64.2 | 87.0 | 188.1 | 256.9 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 56.1 | 77.0 | 164.7 | 262.6 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.4 | 77.0 | 154.9 | 249.2 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 38.1 | 52.0 | 135.7 | 238.8 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 24.0 | 44.0 | 100.6 | 126.2 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.2 | 40.0 | 166.7 | 248.0 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.2 | 41.0 | 96.5 | 123.8 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.2 | 42.0 | 112.9 | 148.5 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.3 | 11.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.6 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 67.7 | 93.0 | 194.2 | 259.2 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 60.0 | 77.0 | 162.2 | 269.9 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.4 | 73.0 | 145.0 | 251.7 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.4 | 55.0 | 129.9 | 236.8 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.8 | 42.0 | 100.0 | 134.5 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.2 | 42.0 | 96.5 | 103.9 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.0 | 76.0 | 84.8 | 94.2 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.6 | 59.0 | 102.6 | 119.5 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.3 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 68.3 | 90.0 | 193.7 | 264.4 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 61.4 | 87.0 | 188.2 | 267.1 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 55.6 | 78.0 | 181.5 | 250.6 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.1 | 57.0 | 154.7 | 246.3 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.0 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 28.5 | 50.0 | 99.0 | 112.8 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 10.0 | 25.0 | 148.7 | 267.6 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.2 | 85.0 | 126.1 | 241.3 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.8 | 50.0 | 103.6 | 137.6 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 8.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.5 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 66.5 | 94.0 | 200.2 | 283.4 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 61.3 | 82.0 | 166.6 | 277.0 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 55.5 | 75.0 | 157.2 | 259.9 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 41.2 | 71.0 | 140.1 | 253.5 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.8 | 51.0 | 142.5 | 227.2 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.6 | 75.0 | 117.2 | 210.1 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.5 | 62.0 | 100.3 | 129.5 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.9 | 71.0 | 144.4 | 233.1 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 63.8 | 94.0 | 187.1 | 286.2 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 56.5 | 81.0 | 157.6 | 277.5 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 53.8 | 87.0 | 145.2 | 263.1 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 43.1 | 82.0 | 144.8 | 272.8 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.7 | 66.0 | 113.8 | 191.7 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.5 | 60.0 | 121.2 | 190.5 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.3 | 78.0 | 107.6 | 143.4 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 35.8 | 54.0 | 168.3 | 237.2 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 61.5 | 91.0 | 179.8 | 267.1 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 56.1 | 94.0 | 151.6 | 280.9 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.5 | 85.0 | 144.4 | 262.5 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 44.0 | 92.0 | 151.9 | 290.4 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.2 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.1 | 67.0 | 123.6 | 153.1 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.6 | 72.0 | 139.3 | 254.8 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.8 | 63.0 | 113.0 | 250.6 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 37.6 | 84.0 | 156.9 | 283.8 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.5 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 53.3 | 98.0 | 170.2 | 289.4 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 54.1 | 100.0 | 142.6 | 282.0 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 51.0 | 100.0 | 130.0 | 256.9 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 45.4 | 97.0 | 144.1 | 295.9 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.4 | 100.0 | 125.2 | 200.6 | 4955 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.4 | 100.0 | 122.1 | 217.5 | 3434 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.4 | 100.0 | 123.2 | 244.5 | 3434 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 40.0 | 86.0 | 155.3 | 292.8 | 4162 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.5 | 146 |

