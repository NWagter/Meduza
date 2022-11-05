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

            ThreadType GetThreadType() const override { return ThreadType::Physics; }

        protected:
            void OnUpdate(float a_dt) override;

        };
    }
}