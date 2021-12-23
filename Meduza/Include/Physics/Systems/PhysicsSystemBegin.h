#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;

        class PhysicsSystemBegin : public BaseSystem<PhysicsComponent,TransformComponent>
        {
        public:
            PhysicsSystemBegin();
            
        protected:
            void OnUpdate(float a_dt) override;
            
        };
    }
}