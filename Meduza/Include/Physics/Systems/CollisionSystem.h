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

            ThreadType GetThreadType() const override { return ThreadType::Physics_Begin; }
            
        protected:
            void OnUpdate(float a_dt) override;
            
        };
    }
}