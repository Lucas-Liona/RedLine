#!/bin/bash

# Create a build directory for SDL2
mkdir -p sdl_build
cd sdl_build

# Download and extract SDL2
wget https://www.libsdl.org/release/SDL2-2.0.22.tar.gz
tar -xzf SDL2-2.0.22.tar.gz
cd SDL2-2.0.22

# Configure and install SDL2 to a local directory
mkdir -p build
cd build
../configure --prefix=$HOME/local
make -j4
make install
cd ../..

# Download and extract SDL2_image
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
tar -xzf SDL2_image-2.0.5.tar.gz
cd SDL2_image-2.0.5

# Configure and install SDL2_image
mkdir -p build
cd build
../configure --prefix=$HOME/local --with-sdl-prefix=$HOME/local
make -j4
make install
cd ../../..

echo "SDL2 and SDL2_image installed successfully"
echo "Add the following to your .bashrc or run before building:"
echo "export PKG_CONFIG_PATH=$HOME/local/lib/pkgconfig:$PKG_CONFIG_PATH"
echo "export LD_LIBRARY_PATH=$HOME/local/lib:$LD_LIBRARY_PATH"

# Add these environment variables to the current session
export PKG_CONFIG_PATH=$HOME/local/lib/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=$HOME/local/lib:$LD_LIBRARY_PATH