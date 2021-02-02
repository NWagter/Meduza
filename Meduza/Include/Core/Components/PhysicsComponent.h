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
            std::vector<CollisionData> m_collided;
            std::vector<CollisionData> m_triggered;
            CollisionType m_collisionType;

            PhysicsLayerID m_physicsLayerId;
            
            PhysicsBody* m_body;
            bool m_gravity = true;

            static ComponentID s_componentID;

            PhysicsComponent()
            {
                m_body = new BodyBox2D();
                m_collisionType = CollisionType::Block;
                m_physicsLayerId = 0;
            }
        };
    }
}