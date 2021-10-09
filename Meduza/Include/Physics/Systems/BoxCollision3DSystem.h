#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;

    namespace Physics
    {        
        struct PhysicsComponent;
        struct BoxCollider3DComponent;

        class BoxCollision3DSystem : public BaseSystem<PhysicsComponent, BoxCollider3DComponent>
        {
        public:
            BoxCollision3DSystem();
            
        protected:
            void OnUpdate(float) override;
            
        };
    }
}