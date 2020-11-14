#pragma once

#include "Components/GameComponents.h"

struct MoveComponent : Me::BaseComponent
{
    bool m_moveUp;
    
    static ComponentID s_componentID;
};