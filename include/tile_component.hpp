#pragma once
#include "ecs.hpp"
#include "transform_component.hpp"
#include "sprite_component.hpp"
#include "collider_component.hpp"

class TileComponent : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    
    SDL_Rect tileRect;
    
    int tileID;
    const char* path;
    
    TileComponent() = default;
    
    TileComponent(int x, int y, int w, int h, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        
        tileID = id;
        
        switch(tileID) {
            default:
                path = "";
                break;
            case 1:
                path = "assets/chair2.png";
                break;
            case 2:
                path = "assets/pole.png";
                break;
        }    
    }
    
    void init() override {
        entity->addComponent<TransformComponent>(
            static_cast<float>(tileRect.x), 
            static_cast<float>(tileRect.y), 
            tileRect.w, 
            tileRect.h, 
            2
        );
        transform = &entity->getComponent<TransformComponent>();
        
        // Only add sprite if we have a valid path
        if (path != nullptr && path[0] != '\0') {
            entity->addComponent<SpriteComponent>(path);
            sprite = &entity->getComponent<SpriteComponent>();
        }
        
        if (tileID == 2) {
            entity->addComponent<ColliderComponent>("pole");
        }
    }
};
