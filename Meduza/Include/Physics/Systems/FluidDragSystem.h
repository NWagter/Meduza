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

            ThreadType GetThreadType() const override { return ThreadType::Physics; }
            
        protected:
            void OnUpdate(float a_dt) override;
            
        };
    }
}