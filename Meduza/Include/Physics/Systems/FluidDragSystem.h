#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;

        class FluidDragSystem : public BaseSystem<PhysicsComponent>
        {
        public:
            FluidDragSystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}