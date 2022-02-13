#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct CircleColliderComponent : public ColliderComponent
        {
            Math::Vec2 m_colliderOffset = Math::Vec2(0, 0);
            float m_radius = 1;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }

            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            virtual void CustomGUI()
            {
                ImGui::DragFloat("Radius", &m_radius);
                Editor::Helper::EditorHelper::DrawVec2Prop("ColliderOffset", m_colliderOffset);
                ColliderComponent::CustomGUI();
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "CircleColliderComponent"; }
        };
    }
}