#pragma once

#include "Components/GameComponents.h"


struct RotateComponent : Me::BaseComponent
{
    float m_rotateSpeed;

    static ComponentID s_componentID;
};