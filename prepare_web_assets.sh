#!/bin/bash

# This script prepares assets for web deployment

# Create assets directory if it doesn't exist
mkdir -p assets

# Copy all PNG and JPG files to assets
find . -name "*.png" -not -path "./assets/*" -not -path "./web_build/*" -exec cp {} assets/ \;
find . -name "*.jpg" -not -path "./assets/*" -not -path "./web_build/*" -exec cp {} assets/ \;

# If there's a game directory with assets, copy them too
if [ -d "game" ]; then
  cp game/*.png assets/ 2>/dev/null || true
  cp game/*.jpg assets/ 2>/dev/null || true
fi

# Create dummy character and chair assets if they don't exist
# (since these are referenced in the code but might not be in your repo)

if [ ! -f "assets/character.png" ]; then
  echo "Creating dummy character.png asset"
  # Create a simple colored square as a placeholder
  convert -size 32x32 xc:blue assets/character.png 2>/dev/null || 
    echo "Warning: ImageMagick not found, couldn't create dummy character.png"
fi

if [ ! -f "assets/chair.png" ]; then
  echo "Creating dummy chair.png asset"
  convert -size 32x32 xc:brown assets/chair.png 2>/dev/null || 
    echo "Warning: ImageMagick not found, couldn't create dummy chair.png"
fi

if [ ! -f "assets/chair2.png" ]; then
  echo "Creating dummy chair2.png asset"
  convert -size 32x32 xc:brown assets/chair2.png 2>/dev/null || 
    echo "Warning: ImageMagick not found, couldn't create dummy chair2.png"
fi

if [ ! -f "assets/pole.png" ]; then
  echo "Creating dummy pole.png asset"
  convert -size 32x32 xc:gray assets/pole.png 2>/dev/null || 
    echo "Warning: ImageMagick not found, couldn't create dummy pole.png"
fi

echo "Assets prepared for web deployment"
