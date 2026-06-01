# TurboPrefill benchmark configuration for llama-server with GPT-OSS-120B.
# Edit MODEL, CONTEXTS_DIR, OUTPUT_DIR and TENSOR_SPLIT for your machine.

MODEL="$HOME/workspace/models/Q4_K_M/gpt-oss-120b-Q4_K_M-00001-of-00002.gguf"
CONTEXTS_DIR="$HOME/workspace/projects/llama.cpp/contexts_gpt_tokenizer"
OUTPUT_DIR="$HOME/workspace/projects/llama.cpp/bench_reports_gpt-120b"

# For 4 identical GPUs use: 1/1/1/1
# For 10 P104-100 GPUs used in early tests: "2/4/4/4/4/4/4/4/3/3"
TENSOR_SPLIT="2/4/4/4/4/4/4/4/3/3"

HOST="0.0.0.0"
PORT=8081

NGL=99
CTX_SIZE=66064
N_GEN=128
BATCH=4096
UBATCH=64
PARALLEL=2

CTK=f16
SPLIT_MODE=layer
TEMPERATURE=0.0
MONITOR_INTERVAL=0.2

# Debug environment passed to llama-server.
# Keep GGML_SCHED_DEBUG=0 for public benchmark runs unless you need scheduler diagnostics.
GGML_SCHED_DEBUG=0
GGML_CUDA_DEBUG=0

