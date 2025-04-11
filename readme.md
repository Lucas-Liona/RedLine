# Redline Game - Web Deployment

This guide explains how to compile and deploy the Redline Game to the web using Emscripten.

## Prerequisites

1. Install Emscripten:
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   ```
   
   Note: On Windows, use `emsdk.bat` instead of `./emsdk` and `emsdk_env.bat` instead of `source ./emsdk_env.sh`.

2. Make sure you have CMake installed (version 3.10 or higher).

3. (Optional) Install ImageMagick for the asset preparation script.

## Project Structure

The web deployment uses the following additional files:

- `CMakeLists.txt` - CMake configuration with Emscripten support
- `shell.html` - Custom HTML template for the web version
- `build_web.sh` - Script to build the web version
- `prepare_web_assets.sh` - Script to prepare assets for web deployment

## Building for Web

1. Make the build scripts executable:
   ```bash
   chmod +x build_web.sh prepare_web_assets.sh
   ```

2. Prepare the assets:
   ```bash
   ./prepare_web_assets.sh
   ```

3. Build the web version:
   ```bash
   ./build_web.sh
   ```

4. The compiled files will be in the `web_build` directory.

## Testing Locally

To test the web version locally:

1. Start a local web server in the build directory:
   ```bash
   cd web_build
   python3 -m http.server
   ```

2. Open a web browser and navigate to `http://localhost:8000`

## Deploying to a Web Server

1. Upload the contents of the `web_build` directory to your web server.

2. Make sure the server is configured to serve the following file types correctly:
   - `.html` as `text/html`
   - `.js` as `application/javascript`
   - `.wasm` as `application/wasm`
   - `.data` as `application/octet-stream`

3. For better performance, configure your server to serve files with gzip compression.

## Troubleshooting

### Game doesn't load or crashes

- Check the browser console for error messages (F12 in most browsers).
- Ensure all required assets are in the `assets` directory.
- Try a different browser (Chrome and Firefox have the best WebAssembly support).

### Performance issues

- Lower the FPS in `main.cpp` to improve performance on lower-end devices.
- Reduce the size and number of assets.
- Make sure your web server is using compression for the `.wasm` and `.data` files.

### Audio doesn't work

- Web browsers require user interaction before allowing audio playback. The custom shell template includes a "Click to Play" button to handle this.

## WebAssembly-Specific Limitations

1. File system access is limited to preloaded files.
2. Performance may vary across browsers and devices.
3. Memory is more constrained than in native builds.

## Advanced Configuration

Check the `CMakeLists.txt` file for additional Emscripten settings you can customize:

- Memory allocation
- Optimization level
- Exported functions
- SDL2 features