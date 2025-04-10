#pragma once

#include "game.hpp"

#define ROW 10
#define COL 5

class Map {
public:
    Map();
    ~Map();

    void LoadMap(int arr[ROW][COL]);
    void DrawMap();
    
private:
    SDL_Rect src, dest;
    SDL_Texture *chair;
    SDL_Texture *pole;
    
    int grid[ROW][COL];
};
