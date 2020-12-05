#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessPawnComponent : Me::BaseComponent
    {
        Pawns m_pawnType;
        Colour m_pawnColour;

        static ComponentID s_componentID;
    };
}