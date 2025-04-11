#pragma once
#include <string>
#include "platform/sdl_includes.hpp"
#include "ecs.hpp"
#include "transform_component.hpp"
#include "game.hpp"

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    std::string tag;
    
    TransformComponent* transform;
    
    ColliderComponent(std::string t) {
        tag = t;
    }
    
    ColliderComponent(std::string t, int w, int h) {
        tag = t;
    }
    
    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        
        transform = &entity->getComponent<TransformComponent>();
        
        if (tag != "player") {
            Game::colliders.push_back(this);
        }
    }
    
    void update() override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};