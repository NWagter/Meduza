#pragma once

#include "Components/GameComponents.h"

struct UpComponent : Me::BaseComponent
{
    float m_upSpeed;

    static ComponentID s_componentID;
};