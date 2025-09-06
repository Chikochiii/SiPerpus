#!/bin/bash
echo "=== Installing SiPerpus ==="

if ! command -v gcc &> /dev/null
then
    echo "❌ GCC not found. Please install GCC first."
    exit
fi

echo "🔧 Compiling the project..."
gcc main.c perpustakaan.c -o perpus

if [ -f "./perpus" ]; then
    echo "✅ Success! Installation completed :D"
else
    echo "❌ Failed to compile the project."
fi

