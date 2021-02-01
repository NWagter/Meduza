#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

#include "Physics/Physics.h"

namespace Me
{
    namespace Physics
    {
        struct PhysicsComponent : public BaseComponent
        {
            std::vector<CollisionData> m_collisionData;
            CollisionType m_collisionType;
            
            PhysicsBody* m_body;
            bool m_gravity = true;

            static ComponentID s_componentID;

            PhysicsComponent()
            {
                m_body = new BodyBox2D();
            }
        };
    }
}