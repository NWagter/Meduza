#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {
        struct PhysicsComponent;

        class BlockingSystem : public BaseSystem<PhysicsComponent, TransformComponent>
        {
        public:
            BlockingSystem();

        protected:
            void OnUpdate(float) override;

        };
    }
}