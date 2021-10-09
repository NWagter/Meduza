#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;

        class PhysicsSystem : public BaseSystem<TagComponent, PhysicsComponent,TransformComponent>
        {
        public:
            PhysicsSystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}