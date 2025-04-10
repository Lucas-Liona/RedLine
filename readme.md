# Redline Game

A 2D game built with SDL2 featuring hexagonal grid movement and collision detection.

## Project Structure

```
redline/
├── .devcontainer/       # GitHub Codespace configuration
├── assets/              # Game assets (images, etc.)
├── build/               # Build artifacts (created by Makefile)
├── include/             # Header files
│   ├── Components.hpp
│   ├── ECS.hpp
│   ├── Game.hpp
│   ├── hex.h
│   └── ...
├── src/                 # Source files
│   ├── Game.cpp
│   ├── main.cpp
│   ├── Map.cpp
│   └── ...
├── Makefile             # Build system
└── README.md            # This file
```

## Setup in GitHub Codespaces

1. Click the "Code" button on your repository
2. Select the "Codespaces" tab
3. Click "Create codespace on main"
4. Wait for the codespace to initialize (this will install all dependencies automatically)

## Building and Running

To build the project:

```bash
make
```

To run the game:

```bash
make run
```

To clean the build artifacts:

```bash
make clean
```

## Dependencies

This project requires:
- SDL2
- SDL2_image

These are automatically installed in the GitHub Codespace environment.

## Controls

- Arrow keys / WASD: Move character
- Space: Jump in the current direction
- J: Light attack
- K: Heavy attack
- L: Special attack
- M: Toggle between game states

## Development

To add new assets:
1. Place your image files in the `assets/` directory
2. Reference them in your code via `assets/yourfile.png`

## License

This project is licensed under the MIT License - see the LICENSE file for details.
