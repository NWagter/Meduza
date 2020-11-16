#pragma once

#include "Components/GameComponents.h"

#include "Math/MeduzaMath.h"

struct MoveComponent : Me::BaseComponent
{
    Me::Math::Vec3 m_destination;
    static ComponentID s_componentID;
};