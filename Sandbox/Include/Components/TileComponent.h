#pragma once

#include "Components/GameComponents.h"

struct PawnComponent;

struct TileComponent : Me::BaseComponent
{
    PawnComponent* m_pawn;
    
    int m_tileX, m_tileY;

    int m_tileId;
    char m_char;

    static ComponentID s_componentID;
};