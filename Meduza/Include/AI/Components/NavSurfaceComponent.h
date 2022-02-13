#pragma once

#include "ECS/BaseComponent.h"

#include "AI/NavField.h"

namespace Me
{
    namespace AI
    {
        struct NavSurfaceComponent : public BaseComponent
        {
            Me::Math::Vec2 m_gridSize;
            Me::Math::Vec2 m_cellSize;

            bool m_generated;
            bool m_printGrid;

            static ComponentID s_componentID;

            void OnChange()
            {
                m_generated = false;
            }

            NavField* Generate()
            {
                m_generated = true;
                return new NavField(m_gridSize, m_cellSize);
            }

            NavSurfaceComponent()
            {
                m_generated = false;
                m_printGrid = false;
            }

            virtual bool RenderCustomGUI() { return false; }
            std::string EditorComponentName() override { return "NavSurfaceComponent"; }
        };
        
    }
}