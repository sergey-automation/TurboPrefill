#!/usr/bin/env bash

# Benchmark configuration for bench_Qwen_3.8.py.
# The benchmark is intended to be launched from the llama.cpp / TurboPrefill checkout being tested.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUN_DIR="$PWD"
BUILD_BIN_DIR="$RUN_DIR/build/bin"

# By default use llama-server from the CURRENT repository directory.
LLAMA_SERVER_BIN="$RUN_DIR/build/bin/llama-server"
LOCAL_LD_LIBRARY_PATH="$RUN_DIR/build/bin"
UNSET_LD_PRELOAD=1


# ==============================================================================
# MODEL + REPORT DIRECTORY
# One MODEL/OUTPUT_DIR pair must be active. Other known local Qwen variants stay commented.
# ==============================================================================

# --- Qwen3.8-27B BF16 ---
# MODEL="/mnt/models/AI/LLM/Qwen3.8-27B-BF16.gguf"
# OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.8-27B-BF16"

# --- Qwen3.8-27B Q8_0 (ACTIVE DEFAULT) ---
MODEL="/mnt/models/AI/LLM/Qwen3.8-27B-Q8_0.gguf"
OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.8-27B-Q8_0"

# --- Qwen3.8-27B Q4_K_M ---
# MODEL="/mnt/models/AI/LLM/Qwen3.8-27B-Q4_K_M.gguf"
# OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.8-27B-Q4_K_M"

# --- Qwen3.6-27B Q8_0 ---
# MODEL="/mnt/models/AI/LLM/Qwen3.6-27B/Qwen3.6-27B-Q8_0.gguf"
# OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.6-27B-Q8_0"

# --- Qwen3.6-27B Q4_K_M (MTP-capable weights; speculative MTP is still OFF unless enabled below) ---
# MODEL="/mnt/models/AI/LLM/Qwen3.6-27B-MTP-Q4_K_M/Qwen3.6-27B-Q4_K_M.gguf"
# OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.6-27B-Q4_K_M"

# --- Qwen3.6-35B-A3B Q8_0 ---
# MODEL="/mnt/models/AI/LLM/Qwen_Qwen3.6-35B-A3B-Q8_0.gguf"
# OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.6-35B-A3B-Q8_0"

# --- Qwen3.6-35B-A3B Q4_K_L ---
# MODEL="/mnt/models/AI/LLM/Qwen_Qwen3.6-35B-A3B-Q4_K_L.gguf"
# OUTPUT_DIR="$RUN_DIR/bench_reports_Qwen3.6-35B-A3B-Q4_K_L"


# Existing context corpus. Change only if another ctx_*.txt directory is required.
CONTEXTS_DIR="$RUN_DIR/contexts_llama3_70b"


# ==============================================================================
# MAIN BENCHMARK SETTINGS
# ==============================================================================

HOST="0.0.0.0"
PORT=8081
NGL=999

# Context / generation.
# CTX_SIZE=131072
CTX_SIZE=260000
# CTX_SIZE=65535
N_GEN=128

# Batch settings.
BATCH=4097
UBATCH=32
PARALLEL=1

# KV K-cache type. V-cache is available separately in ADVANCED SETTINGS below.
CTK=f16

# Layer split is the default benchmark mode.
SPLIT_MODE=layer
# SPLIT_MODE=tensor

# Tensor split for the main model. Six values -> six model-split GPUs.
TENSOR_SPLIT="11/11/11/11/11/9"
# TENSOR_SPLIT="9/11/11/11/11/11"
# TENSOR_SPLIT="10/11/11/11/11/10"

# Explicit physical GPUs. The Python benchmark exposes max(number of entries here,
# number of TENSOR_SPLIT entries). If this list is shorter, it appends the lowest
# available physical GPU indices until the required count is reached.
CUDA_VISIBLE_DEVICES="0,1,2,3,4,5"

# Examples retained from previous experiments:
# CUDA_VISIBLE_DEVICES="7,6,5,4,3,2,1,0"
# CUDA_VISIBLE_DEVICES="0,1,7,8,9,10,11,12,13,14,5,6,2,3,4"
# CUDA_VISIBLE_DEVICES="0,1,7,8,9,10,11,12,13,14"
# TENSOR_SPLIT="5/8/9/9/9/9/9/9/8/6"
# TENSOR_SPLIT="10/16/17/17/17/17/16/10"
# TENSOR_SPLIT="2/6/6/6/6/6/6/6/6/6/6/3"
# TENSOR_SPLIT="4/8/8/8/8/8/8/5"
# TENSOR_SPLIT="8/12/12/12/12/9"
# TENSOR_SPLIT="11/14/14/14/12"
# TENSOR_SPLIT="1/3/3/3/3/3/3/3/3/3/3/3/3/3/1"
# TENSOR_SPLIT="4/7/7/7/7/7/7/7/7/3"

TEMPERATURE=0.15
TURBOPREFILL="${TURBOPREFILL:-0}"
LOG_LEVEL=4

# Debug environment passed to llama-server.
GGML_SCHED_DEBUG=0
GGML_CUDA_DEBUG=0


# ==============================================================================
# OPTIONAL / ADVANCED SETTINGS
# Every parameter below has RU usage notes followed by EN usage notes.
# ==============================================================================

# RU: Разрешить повторное использование KV/prompt cache между запросами. 0 = каждый prompt считается заново; 1 = общий префикс может быть взят из предыдущего запроса.
# EN: Allow KV/prompt cache reuse between requests. 0 = re-evaluate every prompt; 1 = a common prefix may be reused from the previous request.
CACHE_PROMPT=0

# RU: Выполнить один прогревочный запрос до измерений. 1 = прогрев включён; 0 = полностью пропустить пользовательский прогрев.
# EN: Run one benchmark warmup request before measurements. 1 = enabled; 0 = skip the benchmark warmup entirely.
WARMUP=1

# RU: Для прогрева выбрать самый длинный ctx_*.txt, чей размер из имени не превышает этот предел. Пример: 9000 выберет ctx_8192.txt, если он самый длинный <=9000.
# EN: For warmup choose the largest ctx_*.txt whose target size in the filename does not exceed this limit. Example: 9000 selects ctx_8192.txt if it is the largest <=9000.
WARMUP_MAX_TOKENS=9000

# RU: Встроенный пустой warmup самого llama.cpp. 0 = передать --no-warmup и использовать только наш WARMUP выше; 1 = разрешить также штатный warmup llama.cpp.
# EN: llama.cpp built-in empty-run warmup. 0 = pass --no-warmup and use only WARMUP above; 1 = also allow llama.cpp's built-in warmup.
LLAMA_BUILTIN_WARMUP=0

# RU: Оставлять llama-server работающим после benchmark. 1 = оставить сервер; 0 = корректно остановить его SIGINT после теста.
# EN: Keep llama-server running after the benchmark. 1 = leave it running; 0 = stop it gracefully with SIGINT after the test.
KEEP_SERVER_RUNNING=1

# RU: Число повторов каждого сочетания ctx_*.txt и active_slots. 1 сохраняет старое поведение; пример REPEATS=3 добавит три независимых измерения и статистику.
# EN: Number of repeats for each ctx_*.txt and active_slots combination. 1 preserves old behavior; REPEATS=3 adds three measurements and repeat statistics.
REPEATS=1

# RU: Тип V-части KV cache. Примеры: f16, bf16, q8_0. CTK задаётся выше отдельно.
# EN: KV cache V type. Examples: f16, bf16, q8_0. CTK is configured separately above.
CTV=f16

# RU: Flash Attention: auto = выбор llama.cpp, on = принудительно включить, off = принудительно выключить.
# EN: Flash Attention: auto = let llama.cpp decide, on = force enabled, off = force disabled.
FLASH_ATTN=auto

# RU: Потоки CPU для decode/generation. auto = штатный выбор llama.cpp; пример THREADS=8 задаёт 8 потоков.
# EN: CPU threads for decode/generation. auto = llama.cpp default; for example THREADS=8 forces 8 threads.
THREADS=auto

# RU: Потоки CPU для batch/prompt processing. auto = штатный выбор; пример THREADS_BATCH=16.
# EN: CPU threads for batch/prompt processing. auto = llama.cpp default; for example THREADS_BATCH=16.
THREADS_BATCH=auto

# RU: Интервал системного мониторинга в секундах. Пример 2 = GPU/CPU/RAM/swap снимаются примерно раз в 2 секунды.
# EN: System monitoring interval in seconds. Example 2 = sample GPU/CPU/RAM/swap about every 2 seconds.
MONITOR_INTERVAL=2

# RU: Считать SHA256 всего файла модели для отчёта. 0 = не читать десятки гигабайт лишний раз; 1 = считать полный SHA256.
# EN: Compute SHA256 of the full model file for the report. 0 = avoid another tens-of-GB disk read; 1 = compute the complete SHA256.
MODEL_HASH=0

# RU: Vision/mmproj по умолчанию отключён: пустая строка означает text-only запуск. Для Qwen3.8 можно заменить на путь ниже.
# EN: Vision/mmproj is disabled by default: an empty value means text-only mode. For Qwen3.8 replace it with the path shown below.
MMPROJ=""
# MMPROJ="/mnt/models/AI/LLM/Qwen3.8-27B-mmproj-BF16.gguf"
# MMPROJ="/mnt/models/AI/LLM/Qwen3.6-27B/mmproj-F16.gguf"
# MMPROJ="/mnt/models/AI/LLM/mmproj-Qwen_Qwen3.6-35B-A3B-f16.gguf"

# RU: Offload vision/mmproj на GPU, если MMPROJ задан. 1 = GPU offload; 0 = передать --no-mmproj-offload.
# EN: GPU offload for vision/mmproj when MMPROJ is set. 1 = GPU offload; 0 = pass --no-mmproj-offload.
MMPROJ_OFFLOAD=1

# RU: Необязательное устройство vision backend. Пусто = штатный выбор; пример зависит от имён устройств конкретной сборки llama.cpp.
# EN: Optional vision backend device. Empty = default selection; an explicit value depends on device names exposed by the current llama.cpp build.
MTMD_BACKEND_DEVICE=""

# RU: Спекулятивное декодирование по умолчанию полностью выключено. none = без speculation.
# EN: Speculative decoding is fully disabled by default. none = no speculation.
# SPEC_TYPE=none

# RU: Для MTP замените строку выше на SPEC_TYPE=draft-mtp. Число ниже задаёт максимум draft-токенов за шаг.
# EN: For MTP replace the line above with SPEC_TYPE=draft-mtp. The value below sets the maximum number of drafted tokens per step.

SPEC_TYPE=draft-mtp
SPEC_DRAFT_N_MAX=3

# RU: Путь к отдельной draft-модели для режимов draft-simple/draft-eagle3 и т.п. Пусто = отдельная draft-модель не используется.
# EN: Path to a separate draft model for draft-simple/draft-eagle3 and similar modes. Empty = no separate draft model.
SPEC_DRAFT_MODEL=""

# RU: Дополнительные аргументы speculative decoding без изменения Python. Пример: SPEC_EXTRA_ARGS="--spec-ngram-simple-size-n 12 --spec-ngram-simple-size-m 48".
# EN: Extra speculative-decoding CLI arguments without editing Python. Example: SPEC_EXTRA_ARGS="--spec-ngram-simple-size-n 12 --spec-ngram-simple-size-m 48".
SPEC_EXTRA_ARGS=""

# RU: Таймаут ожидания полной загрузки llama-server, секунд. Пример 2400 = ждать до 40 минут для тяжёлой модели/медленного диска.
# EN: Timeout for llama-server model startup, seconds. Example 2400 = wait up to 40 minutes for a large model/slow disk.
SERVER_READY_TIMEOUT_S=2400

# RU: Таймаут одного HTTP benchmark-запроса, секунд. Пример 3600 = до одного часа на очень длинный prompt.
# EN: Timeout for one HTTP benchmark request, seconds. Example 3600 = up to one hour for a very long prompt.
REQUEST_TIMEOUT_S=3600
