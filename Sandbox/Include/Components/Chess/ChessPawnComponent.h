#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessPawnComponent : Me::BaseComponent
    {
        Me::Math::Vec2 m_boardPos;
        
        Pawns m_pawnType;
        Colour m_pawnColour;

        bool m_firstMove = true;

        EntityID m_pawnEntity;
        static ComponentID s_componentID;
    };
}