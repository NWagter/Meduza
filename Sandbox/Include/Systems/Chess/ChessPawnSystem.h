#pragma once

#include "ECS/BaseSystem.h"
#include "Components/Chess/ChessPawnComponent.h"

namespace Me
{
    struct TransformComponent;
}

namespace Chess
{
    class ChessPawnSystem : Me::BaseSystem<ChessPawnComponent, Me::TransformComponent>
    {
    public:
        ChessPawnSystem();

    protected:
        void OnUpdate(float) override;
    };
}