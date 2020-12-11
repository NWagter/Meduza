#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessBoardComponent;

    struct ChessAIComponent : Me::BaseComponent
    {
        ChessBoardComponent* m_board;
        Colour m_aiColour;

        static ComponentID s_componentID;
    };
}