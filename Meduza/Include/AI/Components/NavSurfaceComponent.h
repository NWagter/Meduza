#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    namespace AI
    {
        struct NavSurfaceComponent : public BaseComponent
        {
            Me::Math::Vec2 m_gridSize;
            Me::Math::Vec2 m_cellSize;

            bool m_generated;

            static ComponentID s_componentID;

            void OnChange()
            {
                m_generated = false;
                ME_LOG("Nav Surface Recalc! \n");
            }

            NavSurfaceComponent()
            {
                m_generated = false;
            }
        };
        
    }
}