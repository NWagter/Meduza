#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    struct RenderComponent : BaseComponent
    {
        RenderComponent()
        {
            m_componentID = gs_component++;
        }
    };
}