#pragma once

#include "ECS/BaseSystem.h"

#include "Components/ForwardComponent.h"

namespace Me
{
    struct TransformComponent;
}

class MoveForwardSystem : public Me::BaseSystem<ForwardComponent, Me::TransformComponent>
{
    public:
    MoveForwardSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;
};