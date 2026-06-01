#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 /path/to/llama.cpp" >&2
    exit 1
fi

TARGET="$1"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [[ ! -d "$TARGET" ]]; then
    echo "Target directory not found: $TARGET" >&2
    exit 1
fi

if [[ ! -d "$TARGET/ggml" || ! -d "$TARGET/src" ]]; then
    echo "Target does not look like a llama.cpp checkout: $TARGET" >&2
    exit 1
fi

cp -r "$SCRIPT_DIR/files/"* "$TARGET/"

echo "TurboPrefill files copied to: $TARGET"
echo "Now rebuild llama-server."