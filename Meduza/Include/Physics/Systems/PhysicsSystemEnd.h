#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {
        struct PhysicsComponent;

        class PhysicsSystemEnd : public BaseSystem<PhysicsComponent, TransformComponent>
        {
        public:
            PhysicsSystemEnd();

        protected:
            void OnUpdate(float a_dt) override;

        };
    }
}