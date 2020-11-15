#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
        Math::Vec3 m_position = Math::Vec3(0,0,0);
        Math::Vec3 m_rotation = Math::Vec3(0,0,0);
        float m_uniformScale = 1;

        static ComponentID s_componentID;
    };
}