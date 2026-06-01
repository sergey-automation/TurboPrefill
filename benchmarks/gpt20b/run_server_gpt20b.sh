#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CONFIG_FILE="$SCRIPT_DIR/server_config_20b.sh"

if [[ ! -f "$CONFIG_FILE" ]]; then
    echo "Config not found: $CONFIG_FILE" >&2
    exit 1
fi

# shellcheck source=/dev/null
source "$CONFIG_FILE"

if [[ -x ./build/bin/llama-server ]]; then
    REPO_DIR="$(pwd)"
elif [[ -x "$HOME/workspace/projects/llama.cpp/build/bin/llama-server" ]]; then
    REPO_DIR="$HOME/workspace/projects/llama.cpp"
else
    echo "llama-server not found. Run this from llama.cpp root or build llama.cpp first." >&2
    exit 1
fi

cd "$REPO_DIR"

export GGML_SCHED_DEBUG
export GGML_CUDA_DEBUG

TP_MODE="${TURBOPREFILL:-0}"
echo "Starting GPT-OSS-20B server"
echo "Repo: $REPO_DIR"
echo "Model: $MODEL"
echo "TurboPrefill: $TP_MODE"
echo "Address: http://$HOST:$PORT"

echo "Stopping previous llama-server instances, if any..."
pkill -f llama-server 2>/dev/null || true

exec ./build/bin/llama-server \
    -m "$MODEL" \
    --host "$HOST" \
    --port "$PORT" \
    -ngl "$NGL" \
    -c "$CTX_SIZE" \
    -b "$BATCH" \
    -ub "$UBATCH" \
    -np "$PARALLEL" \
    -ctk "$CTK" \
    -sm "$SPLIT_MODE" \
    -ts "$TENSOR_SPLIT"
