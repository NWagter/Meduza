#pragma once

#include "Components/GameComponents.h"

#include "Math/MeduzaMath.h"

namespace Me
{
    struct TransformComponent;
}

struct CursorComponent;
struct PawnComponent;

struct PlayerComponent : Me::BaseComponent
{    

    Me::TransformComponent* m_cameraTransform;
    CursorComponent* m_cursorComponent;
    PawnComponent* m_selectedPawn;
    
    static ComponentID s_componentID;
};