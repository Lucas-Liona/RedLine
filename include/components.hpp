#pragma once

// Forward declaration first to avoid circular dependencies
class TransformComponent;
class SpriteComponent;
class KeyboardController;
class ColliderComponent;
class TileComponent;

// Then include the actual headers
#include "ecs.hpp"
#include "transform_component.hpp"
#include "sprite_component.hpp"
#include "keyboard_controller.hpp"
#include "collider_component.hpp"
#include "tile_component.hpp"
