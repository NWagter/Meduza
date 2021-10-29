#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Physics.h"

namespace Me
{
    namespace Physics
    {
        struct PhysicsComponent : public BaseComponent
        {
            std::vector<CollisionData> m_collided;
            std::vector<CollisionData> m_triggered;
            
            Math::Vec3 m_position = Math::Vec3(0,0,0);
            Math::Vec3 m_rotation = Math::Vec3(0,0,0);

            Math::Vec3 m_velocity = Math::Vec3(0,0,0);

            float m_bodyMass = 1.0f;
            float m_drag = 1.0f;
            float m_gravityForce;

            bool m_gravity = true;

            static ComponentID s_componentID;

            PhysicsComponent()
            {
                m_gravityForce = gs_gravity;
            }
        };
    }
}