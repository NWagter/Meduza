#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;
        struct BoxCollider2DComponent;

        class BoxCollision2DSystem : public BaseSystem<PhysicsComponent, BoxCollider2DComponent>
        {
        public:
            BoxCollision2DSystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}