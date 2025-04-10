#include "game.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "texture_manager.hpp"
#include "map.hpp"
#include "ecs.hpp"
#include "components.hpp"
#include "vector2D.hpp"
#include "hex.h"

Game::Game() : isRunning(false), cnt(0), window(nullptr) {}

Game::~Game() {}

Map* map;
SDL_Event Game::event;
int Game::state = 0;
std::vector<ColliderComponent*> Game::colliders;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
SDL_Rect* r;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized..." << std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if (window) {
            std::cout << "Window created..." << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created..." << std::endl;
        }
        
        isRunning = true;
        
        // Initialize IMG subsystem
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags)) {
            std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
            isRunning = false;
            return;
        }
        
        map = new Map();
        
        // Set up player and wall entities
        player.addComponent<TransformComponent>(100.0f, 200.0f, 32, 32, 2);
        player.addComponent<SpriteComponent>("assets/character.png");
        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");
        
        wall.addComponent<TransformComponent>(50.0f, 100.0f, 300, 20, 1);
        wall.addComponent<SpriteComponent>("assets/chair.png");
        wall.addComponent<ColliderComponent>("wall");
        
    } else {
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_PollEvent(&event);
    
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    switch (state) {
    case 0:
        manager.refresh();
        manager.update();
        
        for (auto cc : colliders) {
            if(SDL_HasIntersection(&(player.getComponent<ColliderComponent>().collider), &(cc->collider))) {
                std::cout << cc->tag << std::endl;
                
                Vector2D colpos = cc->transform->position;
                Vector2D direction = player.getComponent<TransformComponent>().acceleration;
                Vector2D position = player.getComponent<TransformComponent>().position;
                
                if ((colpos.x - position.x > 0) == (direction.x > 0)) { // Same sign
                    player.getComponent<TransformComponent>().velocity.x = 0;
                    player.getComponent<TransformComponent>().acceleration.x = 0;
                }
                
                if ((colpos.y - position.y > 0) == (direction.y > 0)) { // Same sign
                    player.getComponent<TransformComponent>().velocity.y = 0;
                    player.getComponent<TransformComponent>().acceleration.y = 0;
                }
            }
        }
        break;
    case 1:
        player.update();
        break;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    switch (state) {
    case 0:
        // map->DrawMap();
        manager.draw();
        break;
    case 1:
        SDL_SetRenderDrawColor(renderer, 255, 100, 25, 255);
        SDL_RenderDrawLine(renderer, 0, 0, 10, 10);
        break;
    }
    
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    
    std::cout << "Game Cleaned" << std::endl;
}

void Game::addTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
}
