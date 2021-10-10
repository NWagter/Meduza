#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Physics.h"

namespace Me
{
    namespace Physics
    {
        struct ColliderComponent : public BaseComponent
        {            
            CollisionType m_collisionType;
            CollisionLayerID m_collisionLayer;

            virtual ComponentID GetColliderComponentID()
            {
                return s_componentID;
            }            

            static ComponentID s_componentID;
        };

        struct ColliderTagComponent : public BaseComponent
        {
            ColliderComponent* m_collider;

            static ComponentID s_componentID;

            ColliderTagComponent(ColliderComponent* a_collider)
            {
                m_collider = a_collider;
            }
        };
    }
}