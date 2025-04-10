#include "map.hpp"
#include "texture_manager.hpp"

#define SIZE 32

int lvl2[ROW][COL] = {
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1}
};

Map::Map() {
    chair = TextureManager::LoadTexture("assets/chair2.png");
    pole = TextureManager::LoadTexture("assets/pole.png");

    LoadMap(lvl2);

    src.x = src.y = 0;
    src.w = src.h = SIZE*2;
    dest.w = dest.h = SIZE*2;

    dest.x = dest.y = 0;
}

Map::~Map() {
    SDL_DestroyTexture(chair);
    SDL_DestroyTexture(pole);
}

void Map::LoadMap(int arr[ROW][COL]) {
    for(int row = 0; row < ROW; row++) {
        for(int col = 0; col < COL; col++) {
            Game::addTile(arr[row][col], 
                          col * SIZE*2 + (600 - COL * SIZE*2) / 2, 
                          row * SIZE*2 + (800 - ROW * SIZE*2) / 2);
            grid[row][col] = arr[row][col];
        }
    }
}

void Map::DrawMap() {
    for(int row = 0; row < ROW; row++) {
        for(int col = 0; col < COL; col++) {
            dest.x = col * SIZE*2 + (600 - COL * SIZE*2) / 2;
            dest.y = row * SIZE*2 + (800 - ROW * SIZE*2) / 2;
            
            Game::addTile(grid[row][col], dest.x, dest.y);

            switch(grid[row][col]) {
                case 0:
                    // Empty tile
                    break;
                case 1:
                    TextureManager::Draw(chair, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(pole, src, dest);
                    break;
            }
        }
    }
}
