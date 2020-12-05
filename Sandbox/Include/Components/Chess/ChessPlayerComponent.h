#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessBoardComponent;
    
    struct ChessPlayerComponent : Me::BaseComponent
    {
        ChessBoardComponent* m_board;
        Colour m_playerColour;

        static ComponentID s_componentID;
    };
}