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

            ThreadType GetThreadType() const override { return ThreadType::Physics_End; }

        protected:
            void OnUpdate(float a_dt) override;

        };
    }
}