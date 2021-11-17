#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct CircleColliderComponent : public ColliderComponent
        {
            Math::Vec2 m_colliderOffset = Math::Vec2(0, 0);
            float m_radius = 1;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }

            static ComponentID s_componentID;
        };
    }
}