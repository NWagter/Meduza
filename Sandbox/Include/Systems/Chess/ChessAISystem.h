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
        void OnCreate() override;
        void OnUpdate(float) override;
    };
}