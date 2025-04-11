#!/bin/bash

# Minimal build script for Emscripten
# This script focuses only on getting the basic functionality working

echo "Creating web build directory..."
rm -rf web_build
mkdir -p web_build
cd web_build

# Copy the simplified touch and web input files
cp -f ../include/touch_controller.hpp.simplified ../include/touch_controller.hpp
cp -f ../include/web_input.hpp.simplified ../include/web_input.hpp

# Create platform include directory if it doesn't exist
mkdir -p ../include/platform

# Create SDL includes file
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

# Run CMake with Emscripten
echo "Running CMake with Emscripten toolchain..."
emcmake cmake -DCMAKE_CXX_FLAGS="-sUSE_SDL=2 -sUSE_SDL_IMAGE=2" -DCMAKE_EXE_LINKER_FLAGS="--preload-file assets -sALLOW_MEMORY_GROWTH=1 -O2" ..

# Build the project
echo "Building the project..."
emmake make

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