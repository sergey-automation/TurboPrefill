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
- TURBOPREFILL: `0`
- llama_server_log: `/workspace/bench_reports_gpt-120b_4xRTX3090/20260602_214051/llama_server.log`

## Environment

### TURBOPREFILL

```text
0
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
| ctx_001_000256.txt | 2784 | 128 | 1443.97 | 1.93 | 94.92 | 3.30 |
| ctx_002_000512.txt | 255 | 128 | 688.48 | 0.37 | 97.54 | 1.84 |
| ctx_003_001024.txt | 504 | 128 | 1100.69 | 0.46 | 97.74 | 1.81 |
| ctx_004_002048.txt | 1017 | 128 | 1275.25 | 0.80 | 96.56 | 2.19 |
| ctx_005_004096.txt | 2044 | 128 | 1485.60 | 1.38 | 95.93 | 2.86 |
| ctx_006_006144.txt | 4076 | 128 | 1524.18 | 2.67 | 94.67 | 4.22 |
| ctx_007_008192.txt | 6142 | 128 | 1582.99 | 3.88 | 92.93 | 5.51 |
| ctx_008_012288.txt | 8164 | 128 | 1543.60 | 5.29 | 91.44 | 7.01 |
| ctx_009_016384.txt | 12280 | 128 | 1522.04 | 8.07 | 88.77 | 9.90 |
| ctx_010_024576.txt | 16373 | 128 | 1476.96 | 11.09 | 86.18 | 13.08 |
| ctx_011_032768.txt | 24560 | 128 | 1411.08 | 17.41 | 81.30 | 19.65 |
| ctx_012_065536.txt | 32761 | 128 | 1365.72 | 23.99 | 77.26 | 26.55 |

## GPU load by stage

### ctx_001_000256.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 56.8 | 66.0 | 130.3 | 145.6 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 3.3 | 4.0 | 120.2 | 133.7 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 136.7 | 153.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 22.0 | 58.0 | 124.6 | 128.9 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 34.5 | 66.0 | 136.5 | 145.2 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 17.5 | 22.0 | 122.2 | 126.8 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 15.0 | 20.0 | 143.7 | 147.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 17.0 | 30.0 | 147.8 | 155.3 | 15563 |

### ctx_002_000512.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 134.8 | 134.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 112.9 | 112.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 20.0 | 20.0 | 130.1 | 130.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 30.0 | 30.0 | 137.4 | 137.4 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 20.0 | 24.0 | 129.4 | 135.5 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 20.4 | 22.0 | 115.4 | 122.8 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 20.0 | 20.0 | 134.0 | 142.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 31.8 | 33.0 | 139.4 | 157.7 | 15563 |

### ctx_003_001024.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 19.0 | 19.0 | 133.9 | 136.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 20.0 | 20.0 | 117.0 | 118.0 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 20.0 | 20.0 | 134.7 | 135.3 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 33.0 | 33.0 | 144.9 | 149.6 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.0 | 24.0 | 139.5 | 147.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 124.8 | 132.1 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 21.0 | 21.0 | 139.3 | 145.6 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 31.5 | 33.0 | 148.6 | 158.1 | 15563 |

### ctx_004_002048.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 16.0 | 24.0 | 140.5 | 142.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 124.1 | 125.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 21.0 | 21.0 | 133.7 | 134.1 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 31.0 | 31.0 | 139.9 | 147.2 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 0.0 | 0.0 | 131.6 | 135.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 22.0 | 22.0 | 123.1 | 127.2 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 21.8 | 22.0 | 139.6 | 140.7 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 31.0 | 31.0 | 149.2 | 157.8 | 15563 |

### ctx_005_004096.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 17.2 | 69.0 | 132.2 | 137.2 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 11.0 | 11.0 | 117.3 | 122.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 16.5 | 22.0 | 131.4 | 135.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 64.0 | 97.0 | 135.3 | 149.1 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 69.0 | 69.0 | 141.3 | 146.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 17.0 | 21.0 | 124.6 | 133.8 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 142.1 | 145.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 97.0 | 97.0 | 147.4 | 157.9 | 15563 |

### ctx_006_006144.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 18.0 | 24.0 | 141.9 | 151.5 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 70.4 | 100.0 | 123.7 | 134.8 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 19.2 | 77.0 | 137.3 | 147.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 12.9 | 97.0 | 134.4 | 153.5 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 4.8 | 24.0 | 138.5 | 149.4 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 36.0 | 100.0 | 138.9 | 145.4 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 77.0 | 77.0 | 149.9 | 155.2 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 150.7 | 168.7 | 15563 |

### ctx_007_008192.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 14.0 | 24.0 | 140.6 | 152.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 6.7 | 20.0 | 132.7 | 144.0 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 7.9 | 77.0 | 141.1 | 150.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 20.0 | 30.0 | 135.7 | 164.2 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 10.4 | 13.0 | 138.4 | 146.6 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 4.0 | 20.0 | 138.8 | 145.1 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 18.4 | 23.0 | 145.0 | 150.5 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 18.6 | 31.0 | 145.3 | 157.6 | 15563 |

### ctx_008_012288.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 2.0 | 13.0 | 139.9 | 152.5 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 6.2 | 20.0 | 127.8 | 142.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 52.4 | 99.0 | 138.9 | 151.0 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 5.8 | 31.0 | 132.6 | 154.1 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 21.0 | 21.0 | 142.2 | 150.5 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 10.5 | 21.0 | 136.8 | 143.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 144.9 | 154.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 38.3 | 46.0 | 145.0 | 156.8 | 15563 |

### ctx_009_016384.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 31.4 | 66.0 | 139.3 | 150.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 2.5 | 21.0 | 127.8 | 142.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 139.8 | 151.6 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 51.0 | 91.0 | 130.1 | 146.6 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 11.2 | 57.0 | 134.2 | 143.0 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 7.0 | 21.0 | 138.6 | 145.1 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 10.5 | 21.0 | 149.4 | 155.0 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 42.3 | 67.0 | 149.4 | 167.8 | 15563 |

### ctx_010_024576.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 2.2 | 8.0 | 138.6 | 153.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 7.0 | 56.0 | 128.0 | 140.9 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 31.2 | 100.0 | 139.7 | 151.8 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 1.8 | 30.0 | 131.9 | 156.3 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 1.3 | 8.0 | 135.8 | 151.9 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 44.7 | 56.0 | 136.6 | 144.4 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 95.8 | 100.0 | 151.0 | 155.6 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 149.3 | 168.0 | 15563 |

### ctx_011_032768.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 24.3 | 75.0 | 138.8 | 153.6 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 4.5 | 64.0 | 128.3 | 143.4 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 19.7 | 100.0 | 142.6 | 221.4 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 27.1 | 86.0 | 132.5 | 159.2 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 12.0 | 14.0 | 134.3 | 141.8 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 45.6 | 64.0 | 133.2 | 143.2 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 0.0 | 0.0 | 142.7 | 145.9 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 8.9 | 31.0 | 146.3 | 163.2 | 15563 |

### ctx_012_065536.txt

Prefill stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 53.2 | 100.0 | 138.8 | 149.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 20.3 | 100.0 | 128.9 | 140.5 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 18.4 | 100.0 | 139.4 | 152.0 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 32.6 | 91.0 | 130.9 | 158.5 | 15563 |

Decode stage:

| GPU | name | PCIe | avg util % | max util % | avg W | max W | max VRAM MiB |
|---:|---|---|---:|---:|---:|---:|---:|
| 0 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 8.2 | 22.0 | 138.2 | 145.3 | 18417 |
| 1 | NVIDIA GeForce RTX 3090 | Gen4 x8 | 69.1 | 98.0 | 136.1 | 143.6 | 16145 |
| 2 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 10.5 | 14.0 | 146.4 | 155.8 | 16273 |
| 3 | NVIDIA GeForce RTX 3090 | Gen4 x16 | 65.8 | 78.0 | 143.3 | 158.5 | 15563 |

