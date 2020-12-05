#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessAIComponent : Me::BaseComponent
    {
        static ComponentID s_componentID;
    };
}