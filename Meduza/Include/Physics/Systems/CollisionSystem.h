#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;
        struct ColliderTagComponent;

        class CollisionSystem : public BaseSystem<PhysicsComponent, ColliderTagComponent>
        {
        public:
            CollisionSystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}