#pragma once

#include "ECS/EntityTypes.h"
#include "ECS/BaseComponent.h"

enum class GameComponents : uint16_t
{
    GameComponent = static_cast<uint16_t>(Components::Game),
    MoveComponent    
    
};