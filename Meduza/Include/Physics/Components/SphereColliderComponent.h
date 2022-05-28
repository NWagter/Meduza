#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct SphereColliderComponent : public ColliderComponent
        {
            Math::Vector3 m_colliderOffset = Math::Vector3(0,0,0);
            float m_radius = 1;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }
            
            Math::Vector3 GetFurthestPointInDirection(Math::Matrix4 const& a_transform, Math::Vector3 const& a_direction) const override
            {
                return (Math::Vector3(a_direction).Normalize() * m_radius) + (a_transform.GetPosition() + m_colliderOffset);
            }
            bool Is3DCollider() const override { return true; }
            Math::Vector3 GetColliderScale() const override { return Math::Vector3(m_radius); }

            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            virtual void CustomGUI()
            {
                ImGui::DragFloat("Radius", &m_radius);
                Editor::Helper::EditorHelper::DrawVector3Prop("ColliderOffset", m_colliderOffset);
                ColliderComponent::CustomGUI();
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "SphereColliderComponent"; }
        };
    }
}