#include "SDL2/SDL.h"
#include <iostream>
#include "game.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Game *game = nullptr;
const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

// Main loop function that will be called by Emscripten
void main_loop() {
    frameStart = SDL_GetTicks();
    
    game->handleEvents();
    game->update();
    game->render();
    
    frameTime = SDL_GetTicks() - frameStart;
    
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}

int main(int argc, char **argv) {
    game = new Game();
    
    game->init("Redline", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, false);
    
#ifdef __EMSCRIPTEN__
    // Set up the main loop for Emscripten
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    // Regular loop for native builds
    while (game->running()) {
        main_loop();
    }
    
    game->clean();
    delete game;
#endif

    return 0;
}