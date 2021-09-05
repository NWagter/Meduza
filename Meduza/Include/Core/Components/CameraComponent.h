#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    enum class CameraType : int
    {
        Orthographic,
        Perspective
    };

    struct CameraComponent : public BaseComponent
    {
        CameraComponent()
        {            
            m_near = -0.1f;
            m_far = 1000;
            m_orthoScale = 10;
        }

        Math::Vec2 m_size;
        float m_orthoScale;
        float m_near;
        float m_far;

        CameraType m_cameraType;
        
        static ComponentID s_componentID;
    };
}