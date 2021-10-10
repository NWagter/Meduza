#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;
    struct TagComponent;

    namespace Physics
    {        
        struct PhysicsComponent;
        struct ColliderTagComponent;

        class CollisionSystem : public BaseSystem<TagComponent, PhysicsComponent, ColliderTagComponent>
        {
        public:
            CollisionSystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}