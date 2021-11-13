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
            float m_friction = 1.0f;

            bool m_gravity = true;
            bool m_debugHitNormals = false;

            static ComponentID s_componentID;

        };
    }
}