#pragma once

#include "game.hpp"
#include "ecs.hpp"
#include "transform_component.hpp"

// These should be inside the class or made static, fixed in this version
static bool canJump = true;
static bool canAttack = true;
static const int maxjumps = 3;
static int jumps = 3;

static int speed = 2.3;

static Uint32 callback(Uint32 interval, void* param) {
    if (jumps < maxjumps) {
        jumps++;
    }
    return 0;
}

static Uint32 attack(Uint32 interval, void* param) {
    canAttack = true;
    return 0;
}

class KeyboardController : public Component {
public:
    TransformComponent *transform;
    int cnt;
    
    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        SDL_TimerID timerID = SDL_AddTimer(2000, callback, const_cast<char*>("SDL"));
    }
    
    void update() override {
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        
        transform->acceleration.x = 0;
        transform->acceleration.y = 0;
        
        cnt = 0;
        if(Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_m:
                    if (Game::state == 1) {
                        Game::state = 0;
                    } else {
                        Game::state = 1;
                    }
                    break;
                    
                case SDLK_SPACE:
                    canJump = true;
                    break;
            }
        }
        
        if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) {
            transform->acceleration.y += -speed;
        }
        if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
            transform->acceleration.x += -speed;
        }
        if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) {
            transform->acceleration.y += speed;
        }
        if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
            transform->acceleration.x += speed;
        }

        if (keystates[SDL_SCANCODE_SPACE]) {
            if((jumps > 0) && (canJump)) {
                jumps--;
                canJump = false;
                
                transform->position.x += transform->acceleration.x * 100;
                transform->position.y += transform->acceleration.y * 100;
            }
        }
        
        if (keystates[SDL_SCANCODE_K]) {
            cnt++;
            if(canAttack) {
                canAttack = false;
                std::cout << "heavy";
                SDL_TimerID timerID = SDL_AddTimer(1200, attack, const_cast<char*>("SDL"));
            }
        }
        
        if (keystates[SDL_SCANCODE_L]) {
            cnt++;
            if(canAttack) {
                canAttack = false;
                std::cout << "special";
                SDL_TimerID timerID = SDL_AddTimer(5000, attack, const_cast<char*>("SDL"));
            }
        }
        
        if (keystates[SDL_SCANCODE_J]) {
            cnt++;
            if(canAttack) {
                canAttack = false;
                std::cout << "light";
                SDL_TimerID timerID = SDL_AddTimer(500, attack, const_cast<char*>("SDL"));
            }
        }
        
        if (cnt == 3) {
            std::cout << "PARRY";
        }
    }
};
