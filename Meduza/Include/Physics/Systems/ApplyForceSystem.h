#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    namespace Physics
    {
        struct PhysicsComponent;

        class ApplyForceSystem : public BaseSystem<PhysicsComponent>
        {
        public:
            ApplyForceSystem();

        protected:
            void OnUpdate(float) override;

        };
    }
}