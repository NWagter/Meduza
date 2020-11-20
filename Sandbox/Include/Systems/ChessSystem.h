#pragma once

#include "ECS/BaseSystem.h"
#include "Components/ChessComponent.h"


class ChessSystem : public Me::BaseSystem<ChessComponent>
{
    public:
    ChessSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;

};