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

            static ComponentID s_componentID;
        };
    }
}