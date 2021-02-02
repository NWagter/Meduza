#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    namespace Physics
    {
        struct PhysicsComponent;
    }

    struct TransformComponent;
}

class OverlapSystem : public Me::BaseSystem<Me::Physics::PhysicsComponent, Me::TransformComponent>
{
    public:
    OverlapSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;
};