#!/bin/bash

# Super direct build script for Emscripten
echo "Building for the web..."

# Create build directory
rm -rf web_build
mkdir -p web_build
cd web_build

# Simplify touch_controller.hpp
cat > ../include/touch_controller.hpp << 'EOF'
#pragma once
class TouchController {
public:
    static void init() {}
};
EOF

# Simplify web_input.hpp
cat > ../include/web_input.hpp << 'EOF'
#pragma once
class WebInput {
public:
    static void init() {}
};
EOF

# Create platform includes directory
mkdir -p ../include/platform

# Create SDL includes file
cat > ../include/platform/sdl_includes.hpp << 'EOF'
#pragma once
#ifdef __EMSCRIPTEN__
  #include <SDL.h>
  #include <SDL_image.h>
#else
  #include "SDL2/SDL.h"
  #include "SDL2/SDL_image.h"
#endif
EOF

# Copy assets to current directory first (important!)
mkdir -p assets
cp -r ../assets/* assets/

# Run CMake with correct flags (no preload-file in compiler flags)
emcmake cmake -DCMAKE_CXX_FLAGS="-sUSE_SDL=2 -sUSE_SDL_IMAGE=2" ..

# Build the project with preload-file pointing to the current directory's assets
emmake make EMCC_ARGS="--preload-file assets -sALLOW_MEMORY_GROWTH=1"

echo "Build complete! Run 'cd web_build && python3 -m http.server' to test"