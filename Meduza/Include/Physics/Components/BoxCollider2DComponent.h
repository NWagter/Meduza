#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct BoxCollider2DComponent : public ColliderComponent
        {
            Math::Vec2 m_colliderSize = Math::Vec2(1,1);
            Math::Vec2 m_colliderOffset = Math::Vec2(0,0);

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }
            
            static ComponentID s_componentID;
        };
    }
}