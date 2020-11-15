#pragma once

#include "Components/GameComponents.h"

struct TileComponent : Me::BaseComponent
{
    int m_tileId;
    
    static ComponentID s_componentID;
};