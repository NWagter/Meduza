#pragma once

#include "ECS/BaseSystem.h"
#include "Components/Chess/ChessAIComponent.h"

namespace Chess
{
    class ChessAISystem : Me::BaseSystem<ChessAIComponent>
    {
    public:
        ChessAISystem();


    protected:
        void OnUpdate(float) override;
    };
}