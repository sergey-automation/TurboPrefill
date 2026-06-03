# llama-server context benchmark report

## Test header

- MODEL: `/workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf`
- NGL: `99`
- CTX_SIZE: `66064`
- N_GEN: `128`
- BATCH: `16384`
- UBATCH: `768`
- CTK: `f16`
- SPLIT_MODE: `layer`
- TENSOR_SPLIT: `1/1/1/1`
- PARALLEL: `1`
- TEMPERATURE: `0.0`
- TURBOPREFILL: `1`
- llama_server_log: `/workspace/bench_reports_gpt-120b_4xRTX3090/20260602_214309/llama_server.log`

## Environment

### TURBOPREFILL

```text
1
```

### nvidia_smi

```text
0, NVIDIA GeForce RTX 3090, 580.126.09, 24576 MiB
1, NVIDIA GeForce RTX 3090, 580.126.09, 24576 MiB
2, NVIDIA GeForce RTX 3090, 580.126.09, 24576 MiB
3, NVIDIA GeForce RTX 3090, 580.126.09, 24576 MiB
```

### nvcc

```text
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2025 NVIDIA Corporation
Built on Wed_Aug_20_01:58:59_PM_PDT_2025
Cuda compilation tools, release 13.0, V13.0.88
Build cuda_13.0.r13.0/compiler.36424714_0
```

### cmake

```text
cmake version 3.28.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Server command

```bash
./build/bin/llama-server -m /workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf --host 0.0.0.0 --port 8081 -ngl 99 -c 66064 -b 16384 -ub 768 -np 1 -ctk f16 -sm layer -ts 1/1/1/1
```

## Summary

| File | Prompt tokens | Completion tokens | Prefill tok/s | Prefill time s | Decode tok/s | Wall s |
|---|---:|---:|---:|---:|---:|---:|
| ctx_001_000256.txt | 2784 | 128 | 1617.44 | 1.72 | 95.02 | 3.09 |
| ctx_002_000512.txt | 255 | 128 | 689.02 | 0.37 | 97.86 | 1.84 |
| ctx_003_001024.txt | 504 | 128 | 1104.03 | 0.46 | 97.42 | 1.81 |
| ctx_004_002048.txt | 1017 | 128 | 1273.15 | 0.80 | 96.52 | 2.19 |
| ctx_005_004096.txt | 2044 | 128 | 1478.47 | 1.38 | 96.11 | 2.87 |
| ctx_006_006144.txt | 4076 | 128 | 2169.54 | 1.88 | 94.25 | 3.43 |
| ctx_007_008192.txt | 6142 | 128 | 2454.97 | 2.50 | 93.02 | 4.10 |
| ctx_008_012288.txt | 8164 | 128 | 2648.16 | 3.08 | 91.55 | 4.79 |
| ctx_009_016384.txt | 12280 | 82 | 2761.51 | 4.45 | 88.98 | 5.72 |
| ctx_010_024576.txt | 16373 | 128 | 2758.40 | 5.94 | 86.17 | 7.92 |
| ctx_011_032768.txt | 24560 | 128 | 2413.43 | 10.18 | 81.44 | 12.39 |
| ctx_012_065536.txt | 32761 | 128 | 2335.39 | 14.03 | 77.16 | 16.61 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 2.8 | 7.0 | 132.4 | 144.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 46.2 | 77.0 | 119.1 | 133.7 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 131.9 | 146.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 45.6 | 76.0 | 124.1 | 135.1 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 10.0 | 22.0 | 140.0 | 147.1 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 4.4 | 22.0 | 125.4 | 127.5 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 16.0 | 20.0 | 142.5 | 149.8 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 76.0 | 76.0 | 150.4 | 160.6 | 15563 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 140.0 | 140.0 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 118.6 | 118.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 20.0 | 20.0 | 132.2 | 132.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 146.7 | 146.7 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 139.1 | 147.6 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 116.9 | 122.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 21.6 | 22.0 | 133.0 | 142.0 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 142.0 | 157.0 | 15563 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 143.1 | 145.0 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 115.2 | 116.4 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 22.0 | 22.0 | 134.5 | 135.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 3.0 | 3.0 | 141.8 | 148.2 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.5 | 24.0 | 133.1 | 135.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 21.8 | 22.0 | 116.6 | 118.5 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 22.0 | 22.0 | 138.2 | 144.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 3.0 | 3.0 | 148.6 | 157.1 | 15563 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 132.9 | 138.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 21.0 | 21.0 | 114.3 | 116.3 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 34.3 | 59.0 | 132.0 | 132.3 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 138.7 | 145.3 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 140.7 | 147.4 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 21.0 | 21.0 | 128.8 | 134.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 59.0 | 59.0 | 138.1 | 143.3 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 8.2 | 33.0 | 149.3 | 157.1 | 15563 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 137.8 | 145.4 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 21.0 | 21.0 | 121.2 | 128.8 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 59.0 | 59.0 | 130.7 | 134.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 33.0 | 33.0 | 135.6 | 148.2 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 141.0 | 147.2 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 21.0 | 21.0 | 130.3 | 136.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 36.8 | 59.0 | 142.1 | 145.4 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 31.4 | 33.0 | 145.9 | 156.8 | 15563 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 154.1 | 163.0 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 53.5 | 86.0 | 132.5 | 143.4 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 38.0 | 54.0 | 139.9 | 161.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 10.3 | 31.0 | 136.0 | 150.8 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 1.0 | 1.0 | 142.7 | 146.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 59.6 | 86.0 | 123.8 | 130.3 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 40.8 | 54.0 | 145.8 | 156.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 6.4 | 32.0 | 150.8 | 158.8 | 15563 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 27.3 | 87.0 | 154.5 | 180.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 77.1 | 100.0 | 134.9 | 172.4 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 38.1 | 51.0 | 146.4 | 169.7 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 29.7 | 32.0 | 140.1 | 162.6 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 87.0 | 87.0 | 134.9 | 140.7 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 69.2 | 100.0 | 135.7 | 143.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 148.8 | 153.4 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 16.0 | 16.0 | 147.3 | 165.3 | 15563 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 86.7 | 92.0 | 155.4 | 191.1 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 31.6 | 41.0 | 142.7 | 181.7 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 14.4 | 36.0 | 147.7 | 178.7 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 32.4 | 45.0 | 141.6 | 167.3 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 54.0 | 54.0 | 135.7 | 146.5 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 1.0 | 1.0 | 135.3 | 144.2 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 27.0 | 36.0 | 146.3 | 154.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 39.4 | 45.0 | 157.5 | 169.2 | 15563 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 42.9 | 100.0 | 156.0 | 191.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 48.7 | 95.0 | 147.7 | 181.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 22.3 | 83.0 | 152.2 | 178.5 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 10.9 | 31.0 | 146.5 | 173.7 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 0.0 | 0.0 | 134.4 | 140.0 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 95.0 | 95.0 | 136.3 | 138.8 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 83.0 | 83.0 | 147.0 | 150.4 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 13.0 | 31.0 | 136.1 | 141.3 | 15563 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 52.3 | 100.0 | 160.2 | 191.2 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 48.6 | 95.0 | 146.9 | 183.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 36.4 | 91.0 | 152.1 | 179.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 36.3 | 77.0 | 142.8 | 169.9 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 39.7 | 69.0 | 145.2 | 148.6 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 27.7 | 39.0 | 133.3 | 147.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 3.8 | 23.0 | 145.7 | 156.7 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 40.3 | 45.0 | 147.7 | 159.6 | 15563 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 48.5 | 100.0 | 157.8 | 192.1 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 30.1 | 92.0 | 145.5 | 181.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 39.1 | 95.0 | 149.9 | 181.8 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 21.6 | 87.0 | 138.8 | 167.3 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 11.6 | 81.0 | 138.0 | 145.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 9.4 | 22.0 | 133.7 | 143.7 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 36.7 | 59.0 | 139.2 | 146.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 9.1 | 32.0 | 146.6 | 154.7 | 15563 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 61.1 | 100.0 | 155.3 | 193.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 32.1 | 86.0 | 141.2 | 182.2 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 20.7 | 45.0 | 148.5 | 182.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 33.8 | 69.0 | 139.9 | 170.0 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 48.8 | 95.0 | 138.4 | 145.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 5.0 | 20.0 | 136.0 | 143.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 30.5 | 35.0 | 139.9 | 148.6 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 9.1 | 44.0 | 145.9 | 160.2 | 15563 |

