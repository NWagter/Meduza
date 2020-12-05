#pragma once

#include "ECS/BaseSystem.h"
#include "Components/Chess/ChessPlayerComponent.h"

namespace Chess
{
    class ChessPlayerSystem : Me::BaseSystem<ChessPlayerComponent>
    {
    public:
        ChessPlayerSystem();


    protected:
        void OnUpdate(float) override;
    };
}