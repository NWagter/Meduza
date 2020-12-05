#pragma once

#include "ECS/BaseSystem.h"
#include "Components/Chess/ChessPawnComponent.h"

namespace Chess
{
    class ChessPawnSystem : Me::BaseSystem<ChessPawnComponent>
    {
    public:
        ChessPawnSystem();


    protected:
        void OnUpdate(float) override;
    };
}