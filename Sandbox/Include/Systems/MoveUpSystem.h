#pragma once

#include "ECS/BaseSystem.h"

#include "Components/UpComponent.h"

namespace Me
{
    struct TransformComponent;
}

class MoveUpSystem : public Me::BaseSystem<UpComponent, Me::TransformComponent>
{
    public:
    MoveUpSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;
};