#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessPawnComponent;  
    
    struct ChessBoardComponent : Me::BaseComponent
    {
        ChessPawnComponent* m_board[gs_boardWidth][gs_boardHeight];

        Colour m_activePlayer;

        static ComponentID s_componentID;
    };
}