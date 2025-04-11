#!/bin/bash

# This script starts a local web server to test the game

# Check if the web_build directory exists
if [ ! -d "web_build" ]; then
    echo "Error: web_build directory not found!"
    echo "Please run './build_web.sh' first to build the game."
    exit 1
fi

# Navigate to the web_build directory
cd web_build

# Check if Python 3 is available
if command -v python3 &> /dev/null; then
    echo "Starting web server with Python 3..."
    echo "Open your browser and navigate to: http://localhost:8000"
    python3 -m http.server
elif command -v python &> /dev/null; then
    # Check Python version
    python_version=$(python --version 2>&1)
    if [[ $python_version == *"Python 3"* ]]; then
        echo "Starting web server with Python..."
        echo "Open your browser and navigate to: http://localhost:8000"
        python -m http.server
    else
        echo "Starting web server with Python 2..."
        echo "Open your browser and navigate to: http://localhost:8000"
        python -m SimpleHTTPServer 8000
    fi
else
    echo "Error: Python not found!"
    echo "Please install Python to run the web server."
    exit 1
fi