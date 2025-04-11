#pragma once
#ifdef __EMSCRIPTEN__
  #include <SDL.h>
  #include <SDL_image.h>
#else
  #include "SDL2/SDL.h"
  #include "SDL2/SDL_image.h"
#endif
