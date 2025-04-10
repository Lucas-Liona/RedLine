#!/bin/bash

# Create the directory structure
mkdir -p include src assets build .devcontainer

# Copy header files to the include directory
cp *.h include/ 2>/dev/null || true
cp *.hpp include/ 2>/dev/null || true

# Copy source files to the src directory
cp *.cpp src/ 2>/dev/null || true

# Create assets directory and copy assets
mkdir -p assets
# Copy any png, jpg, etc. files to assets
cp *.png assets/ 2>/dev/null || true
cp *.jpg assets/ 2>/dev/null || true

# If there's a game directory with assets, copy them too
if [ -d "game" ]; then
  cp game/*.png assets/ 2>/dev/null || true
  cp game/*.jpg assets/ 2>/dev/null || true
fi

echo "Directory structure set up successfully!"
echo "Next steps:"
echo "1. Run 'make' to build the project"
echo "2. Run './redline' to start the game"
