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
- TURBOPREFILL: `0`
- llama_server_log: `/run/media/ilnur/ssd_fleshka/llama.cpp-turboprefill/bench_reports_gpt-20b/20260707_195348/llama_server.log`

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
./build/bin/llama-server -m /run/media/ilnur/ssd_fleshka/gpt-oss-20b-F16.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66096 -b 8192 -ub 32 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 255 | 128 | 132.21 | 1.93 | 47.05 | 6.01 |
| ctx_002_000512.txt | 504 | 128 | 231.46 | 2.18 | 48.32 | 5.33 |
| ctx_003_001024.txt | 1017 | 128 | 259.57 | 3.92 | 48.61 | 7.34 |
| ctx_004_002048.txt | 2044 | 128 | 290.91 | 7.03 | 49.09 | 10.78 |
| ctx_005_004096.txt | 4076 | 128 | 296.29 | 13.76 | 47.92 | 17.06 |
| ctx_006_006144.txt | 6142 | 128 | 293.00 | 20.96 | 47.73 | 24.25 |
| ctx_007_008192.txt | 8164 | 128 | 288.59 | 28.29 | 46.97 | 31.84 |
| ctx_008_012288.txt | 12280 | 128 | 278.17 | 44.15 | 46.97 | 47.69 |
| ctx_009_016384.txt | 16373 | 128 | 282.37 | 57.98 | 45.93 | 61.72 |
| ctx_010_024576.txt | 24560 | 128 | 264.16 | 92.97 | 45.04 | 97.07 |
| ctx_011_032768.txt | 32761 | 128 | 241.82 | 135.47 | 40.30 | 140.35 |
| ctx_012_065536.txt | 64423 | 128 | 181.79 | 354.39 | 36.29 | 360.23 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 0.0 | 0.0 | 60.7 | 61.7 | 4822 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 71.6 | 88.6 | 3312 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 67.6 | 77.7 | 3312 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 0.0 | 0.0 | 76.6 | 76.7 | 3982 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.5 | 23.0 | 77.2 | 96.0 | 4822 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.2 | 20.0 | 81.5 | 134.0 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.3 | 19.0 | 76.0 | 132.8 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.2 | 37.0 | 113.4 | 144.2 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 10.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.9 | 146 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 17.2 | 39.0 | 68.4 | 92.5 | 4822 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 11.8 | 20.0 | 91.2 | 138.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.1 | 34.0 | 71.5 | 90.7 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 6.2 | 11.0 | 92.3 | 136.3 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.9 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 20.9 | 22.0 | 73.2 | 89.4 | 4822 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.8 | 19.0 | 80.6 | 139.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.5 | 27.0 | 74.2 | 135.6 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.3 | 38.0 | 106.8 | 119.3 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 11.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.9 | 146 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.9 | 43.0 | 86.0 | 170.5 | 4822 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 17.7 | 32.0 | 82.2 | 132.3 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.7 | 30.0 | 84.2 | 126.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 8.4 | 19.0 | 105.1 | 188.3 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 8.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 19.8 | 21.0 | 89.1 | 173.2 | 4822 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.6 | 23.0 | 79.5 | 89.3 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.4 | 31.0 | 75.6 | 86.6 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.2 | 39.0 | 128.0 | 160.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 146 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.8 | 44.0 | 106.0 | 213.3 | 5000 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.0 | 36.0 | 83.9 | 143.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.5 | 34.0 | 78.9 | 132.3 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 11.2 | 19.0 | 104.7 | 194.5 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 11.1 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 23.6 | 37.0 | 102.2 | 166.8 | 5002 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.4 | 36.0 | 81.8 | 125.5 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.4 | 28.0 | 77.9 | 98.4 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.5 | 39.0 | 130.7 | 161.3 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 11.5 | 146 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.2 | 37.0 | 114.2 | 232.6 | 5002 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.5 | 37.0 | 89.2 | 140.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.9 | 37.0 | 81.6 | 138.4 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 14.3 | 22.0 | 82.9 | 191.1 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.7 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.5 | 38.0 | 111.0 | 219.6 | 5002 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.8 | 32.0 | 87.1 | 140.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.2 | 30.0 | 75.0 | 82.9 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.8 | 45.0 | 108.7 | 132.9 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 10.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 146 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.2 | 41.0 | 110.0 | 208.0 | 5002 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.4 | 38.0 | 90.3 | 145.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.8 | 37.0 | 81.4 | 137.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 15.8 | 29.0 | 87.3 | 149.3 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.9 | 11.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.4 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.7 | 40.0 | 91.6 | 102.3 | 5001 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.8 | 39.0 | 77.3 | 84.3 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.9 | 36.0 | 77.1 | 140.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 33.6 | 39.0 | 100.1 | 116.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.9 | 146 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.5 | 39.0 | 118.5 | 215.0 | 5001 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 28.0 | 41.0 | 92.2 | 151.9 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.3 | 39.0 | 81.8 | 137.3 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.4 | 29.0 | 82.3 | 149.0 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 10.6 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.3 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.4 | 35.0 | 105.2 | 136.1 | 5001 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.9 | 38.0 | 91.5 | 142.6 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.9 | 39.0 | 80.8 | 135.7 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.4 | 41.0 | 99.4 | 131.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.0 | 146 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 27.3 | 41.0 | 134.9 | 261.8 | 5143 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.9 | 42.0 | 96.0 | 181.0 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.4 | 40.0 | 84.9 | 148.9 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 16.4 | 38.0 | 81.3 | 142.9 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 11.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 21.2 | 28.0 | 117.8 | 178.9 | 5001 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.2 | 39.0 | 98.3 | 162.7 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.5 | 35.0 | 76.3 | 92.7 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 34.4 | 43.0 | 95.5 | 125.6 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.0 | 146 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.3 | 43.0 | 136.3 | 255.8 | 5001 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.6 | 55.0 | 127.2 | 237.0 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.7 | 40.0 | 95.0 | 177.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 18.3 | 40.0 | 92.7 | 210.7 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.4 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.8 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.8 | 39.0 | 140.8 | 226.3 | 5001 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 21.7 | 36.0 | 91.5 | 104.2 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.4 | 34.0 | 80.0 | 94.6 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.3 | 40.0 | 101.5 | 136.9 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 9.0 | 12.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 9.2 | 146 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 29.3 | 45.0 | 142.3 | 258.4 | 5012 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.3 | 63.0 | 126.9 | 244.0 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.3 | 73.0 | 120.5 | 243.4 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.2 | 36.0 | 78.1 | 183.6 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.8 | 12.3 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.6 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.5 | 34.0 | 133.5 | 223.6 | 5010 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.7 | 34.0 | 139.6 | 230.8 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.7 | 35.0 | 82.7 | 98.5 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 32.2 | 41.0 | 99.1 | 134.5 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 9.2 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 9.0 | 146 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 28.1 | 43.0 | 130.6 | 261.4 | 5010 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 27.4 | 91.0 | 106.6 | 247.1 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 24.4 | 41.0 | 101.7 | 234.8 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 19.6 | 89.0 | 76.8 | 186.9 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.1 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 22.9 | 30.0 | 88.8 | 156.3 | 5008 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.1 | 29.0 | 88.1 | 138.6 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 22.3 | 34.0 | 74.5 | 91.0 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 30.3 | 41.0 | 89.3 | 120.8 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 10.0 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.4 | 9.1 | 146 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 26.7 | 43.0 | 100.1 | 264.9 | 5010 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 26.4 | 68.0 | 92.8 | 246.5 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 25.9 | 65.0 | 84.5 | 229.1 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.4 | 73.0 | 77.7 | 175.6 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.7 | 12.5 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 11.5 | 146 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce GTX 1080 Ti | Gen3 x16 | 25.6 | 39.0 | 77.0 | 104.2 | 4823 |
| 1 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 23.9 | 39.0 | 88.0 | 161.5 | 3364 |
| 2 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 20.8 | 38.0 | 87.8 | 167.9 | 3364 |
| 3 | NVIDIA GeForce GTX 1080 Ti | Gen2 x1 | 31.0 | 41.0 | 93.5 | 154.0 | 4034 |
| 4 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.5 | 8.8 | 146 |
| 5 | NVIDIA GeForce GTX 1080 Ti | Gen1 x1 | 0.0 | 0.0 | 8.6 | 10.8 | 146 |

