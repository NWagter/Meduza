#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    namespace Physics
    {
        struct ColliderComponent : public BaseComponent
        {            
            CollisionType m_collisionType;
            CollisionLayerID m_collisionLayer;

            static ComponentID s_componentID;
        };
    }
}