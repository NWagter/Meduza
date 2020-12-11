#pragma once

#include "Components/GameComponents.h"
#include "Math/MeduzaMath.h"

struct CursorComponent : Me::BaseComponent
{
    Me::Math::Vec3 m_position;
    bool m_enabled = true;
    
    static ComponentID s_componentID;
};