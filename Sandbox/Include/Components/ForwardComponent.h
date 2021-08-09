#pragma once

#include "Components/GameComponents.h"

struct ForwardComponent : Me::BaseComponent
{
    float m_forwardSpeed;

    static ComponentID s_componentID;
};