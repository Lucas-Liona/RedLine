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

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    echo "CMake not found! Please install it with:"
    echo "sudo apt-get install cmake"
    exit 1
fi

# Create build directory
echo "Creating web build directory..."
rm -rf web_build
mkdir -p web_build
cd web_build

# Create platform-specific SDL includes if needed
mkdir -p ../include/platform
if [ ! -f "../include/platform/sdl_includes.hpp" ]; then
    echo "Creating platform-specific SDL includes header..."
    cat > ../include/platform/sdl_includes.hpp << 'EOF'
#pragma once

// This header handles SDL include differences between native builds and Emscripten web builds

#ifdef __EMSCRIPTEN__
  // Emscripten's SDL ports use different include paths
  #include <SDL.h>
  #include <SDL_image.h>
#else
  // Native build uses standard include paths
  #include "SDL2/SDL.h"
  #include "SDL2/SDL_image.h"
#endif
EOF
fi

# Run CMake with Emscripten
echo "Running CMake with Emscripten toolchain..."
emcmake cmake ..

# Build the project with verbose output to see all compiler flags
echo "Building the project..."
emmake make VERBOSE=1

# Check if build was successful
if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo "To run the game:"
    echo "cd web_build"
    echo "python3 -m http.server"
    echo "Then open a browser and navigate to http://localhost:8000"
else
    echo ""
    echo "Build failed. Please check the errors above."
fi