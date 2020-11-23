#pragma once
#include "Components/GameComponents.h"

#include "Components/TileComponent.h"

struct ChessBoardComponent : Me::BaseComponent
{
    TileComponent* m_chessBoard[8][8];

    static ComponentID s_componentID;
};