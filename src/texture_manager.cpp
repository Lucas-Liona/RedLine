#include "TextureManager.hpp"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << texture << " Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (!tex) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(tempSurface);
    
    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    if (tex) {
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    }
}
