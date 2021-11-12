#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {
        struct PhysicsComponent;

        class FrictionSystem : public BaseSystem<PhysicsComponent>
        {
        public:
            FrictionSystem();

        protected:
            void OnUpdate(float) override;

        };
    }
}