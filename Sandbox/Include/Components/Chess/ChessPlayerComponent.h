#pragma once

#include "Components/GameComponents.h"

#include "Games/Chess/ChessHelper.h"

namespace Chess
{
    struct ChessPlayerComponent : Me::BaseComponent
    {
        static ComponentID s_componentID;
    };
}