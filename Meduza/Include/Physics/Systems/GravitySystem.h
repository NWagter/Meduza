#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;

        class GravitySystem : public BaseSystem<PhysicsComponent>
        {
        public:
            GravitySystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}