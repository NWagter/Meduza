#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct SphereColliderComponent : public ColliderComponent
        {
            Math::Vec3 m_colliderOffset = Math::Vec3(0,0,0);
            float m_radius = 1;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }
            
            static ComponentID s_componentID;
        };
    }
}