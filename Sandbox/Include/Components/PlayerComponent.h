#pragma once

#include "Components/GameComponents.h"

#include "Math/MeduzaMath.h"

namespace Me
{
    struct TransformComponent;
}

struct CursorComponent;

struct PlayerComponent : Me::BaseComponent
{    
    Me::TransformComponent* m_cameraTransform;
    CursorComponent* m_cursorComponent;
    
    static ComponentID s_componentID;
};