# TurboPrefill benchmark configuration for llama-server.
# Edit MODEL, CONTEXTS_DIR, OUTPUT_DIR and TENSOR_SPLIT for your machine.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

MODEL="/workspace/models/gpt-oss-20b-Q4_K_M.gguf"
CONTEXTS_DIR="$SCRIPT_DIR/contexts_gpt_tokenizer"
OUTPUT_DIR="$SCRIPT_DIR/bench_reports_gpt-20b"

# For 4 identical GPUs use: 1/1/1/1
# For 10 P104-100 GPUs used in early tests: 2/4/4/4/4/4/4/4/3/3
TENSOR_SPLIT="1/1/1/1"

HOST="0.0.0.0"
PORT=8081

NGL=99
CTX_SIZE=66096
N_GEN=128
BATCH=16384



UBATCH=32
PARALLEL=1

CTK=f16
SPLIT_MODE=layer
TEMPERATURE=0.0
MONITOR_INTERVAL=0.2

# Debug environment passed to llama-server.
# Keep GGML_SCHED_DEBUG=0 for public benchmark runs unless you need scheduler diagnostics.
GGML_SCHED_DEBUG=0
GGML_CUDA_DEBUG=0

