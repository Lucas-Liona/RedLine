#!/bin/bash

# Check if Emscripten is available
if ! command -v emcc &> /dev/null; then
    echo "Emscripten compiler (emcc) not found!"
    echo "Please install and activate Emscripten first:"
    echo "git clone https://github.com/emscripten-core/emsdk.git"
    echo "cd emsdk"
    echo "./emsdk install latest"
    echo "./emsdk activate latest"
    echo "source ./emsdk_env.sh"
    exit 1
fi

# Create build directory
mkdir -p web_build
cd web_build

# Run CMake with Emscripten
emcmake cmake ..

# Build the project
emmake make

echo ""
echo "Build complete! To run the game:"
echo "cd web_build"
echo "python3 -m http.server"
echo "Then open a browser and navigate to http://localhost:8000"
