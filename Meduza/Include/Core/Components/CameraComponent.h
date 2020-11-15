#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    enum class CameraType
    {
        Orthographic,
        Perspective
    };

    struct CameraComponent : public BaseComponent
    {
        Math::Vec4 m_frustrum;
        float m_near;
        float m_far;

        CameraType m_cameraType;
        
        static ComponentID s_componentID;
    };
}