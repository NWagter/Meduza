#pragma once

#include "Components/GameComponents.h"

#include "Components/PawnComponent.h"

struct ChessComponent : Me::BaseComponent
{
    PawnComponent* m_movingPawn;
    PawnColour m_turn;

    static ComponentID s_componentID;
};