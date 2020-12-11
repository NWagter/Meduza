#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessBoardComponent;
    struct ChessPawnComponent;
    
    struct ChessPlayerComponent : Me::BaseComponent
    {
        ChessBoardComponent* m_board;
        Colour m_playerColour;

        ChessPawnComponent* m_selectedPawn = nullptr;
        std::vector<std::pair<int,int>> m_possibleMoves;

        static ComponentID s_componentID;
    };
}