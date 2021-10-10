#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components//ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct BoxCollider3DComponent : public ColliderComponent
        {
            Math::Vec3 m_colliderSize = Math::Vec3(1,1,1);
            Math::Vec3 m_colliderOffset = Math::Vec3(0,0,0);

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }

            static ComponentID s_componentID;
        };
    }
}