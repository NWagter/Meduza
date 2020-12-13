#pragma once

#include "ECS/BaseSystem.h"

#include "Components/RotateComponent.h"

namespace Me
{
    struct TransformComponent;
}

class Rotator : public Me::BaseSystem<RotateComponent, Me::TransformComponent>
{
    public:
    Rotator();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;
};