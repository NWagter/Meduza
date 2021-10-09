#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;

        class GravitySystem : public BaseSystem<PhysicsComponent,TransformComponent>
        {
        public:
            GravitySystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}