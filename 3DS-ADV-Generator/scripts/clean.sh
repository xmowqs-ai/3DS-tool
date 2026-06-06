#!/bin/bash

# Clean Build Artifacts

echo "🧹 Cleaning build artifacts..."
echo ""

if [ $# -eq 0 ]; then
    echo "Cleaning all projects..."
    find . -name "build" -type d -exec rm -rf {} + 2>/dev/null || true
    find . -name "game_src" -type d -exec rm -rf {} + 2>/dev/null || true
    find . -name "*.o" -delete 2>/dev/null || true
    find . -name "*.3dsx" -delete 2>/dev/null || true
    find . -name "*.elf" -delete 2>/dev/null || true
else
    echo "Cleaning: $1"
    rm -rf "$1/game_src" 2>/dev/null || true
fi

echo "✓ Clean complete!"
