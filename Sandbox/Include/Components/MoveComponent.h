#pragma once

#include "Components/GameComponents.h"

struct MoveComponent : Me::BaseComponent
{
    bool m_moveRight = true;
    
    static ComponentID s_componentID;
};