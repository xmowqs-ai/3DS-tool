#!/bin/bash

# 3DS ADV Generator Build Script

set -e

if [ $# -eq 0 ]; then
    echo "Usage: ./build.sh <project_directory>"
    echo "Example: ./build.sh examples/simple_story"
    exit 1
fi

PROJECT_DIR="$1"
OUTPUT_DIR="${PROJECT_DIR}/game_src"

echo "🎮 3DS ADV Generator Build System"
echo "================================="
echo ""
echo "Project: $PROJECT_DIR"
echo ""

if [ ! -f "${PROJECT_DIR}/story.json" ]; then
    echo "Error: story.json not found in $PROJECT_DIR"
    exit 1
fi

echo "[1/3] Validating JSON..."
if ! ./adv-tool/bin/adv-tool validate "${PROJECT_DIR}/story.json"; then
    echo "Error: JSON validation failed"
    exit 1
fi

echo ""
echo "[2/3] Generating C code..."
if ! ./adv-tool/bin/adv-tool generate "${PROJECT_DIR}/story.json" -o "${OUTPUT_DIR}"; then
    echo "Error: Code generation failed"
    exit 1
fi

echo ""
echo "[3/3] Building 3DSX..."
cd "${OUTPUT_DIR}"
make clean || true
make

echo ""
echo "✓ Build complete!"
echo ""
echo "Output: ${OUTPUT_DIR}/game.3dsx"
echo ""
echo "To run:"
echo "  - Emulator (Citra): citra-qt ${OUTPUT_DIR}/game.3dsx"
echo "  - 3DS: Copy game.3dsx to /3ds/ on your SD card"
