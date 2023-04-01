#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct BoxCollider3DComponent : public ColliderComponent
        {
            Math::Vector3 m_colliderSize = Math::Vector3(1,1,1);
            Math::Vector3 m_colliderOffset = Math::Vector3(0,0,0);
            std::vector<HullVertex> m_points;

            ComponentID GetColliderComponentID() const override
            {
                return s_componentID;
            }

            Math::Vector3 GetFurthestPointInDirection(Math::Matrix4 const& a_transform, Math::Vector3 const& a_direction) const override
            {
                Math::Vector3 point(PhysicsHelper::GetFurthestPointInDirection(a_transform, a_direction, m_points, m_colliderSize, m_colliderOffset));
                return point;
            }
            bool Is3DCollider() const override { return true; }
            Math::Vector3 GetColliderScale() const override { return Math::Vector3(m_colliderSize.m_x, m_colliderSize.m_y, m_colliderSize.m_z); }

            BoxCollider3DComponent()
            {
                // Front
                m_points.push_back(HullVertex(Math::Vector3(-0.5f, -0.5f, 0.5f), Colours::TAUBMANS_WINTER_OAK));
                m_points.push_back(HullVertex(Math::Vector3(-0.5f, 0.5f, 0.5f), Colours::BLACK));
                m_points.push_back(HullVertex(Math::Vector3(0.5f, 0.5f, 0.5f), Colours::AZURE_WHITE));
                m_points.push_back(HullVertex(Math::Vector3(0.5f, -0.5f, 0.5f), Colours::MAGENTA));
                // Back
                m_points.push_back(HullVertex(Math::Vector3(-0.5f, -0.5f, -0.5f), Colours::RESENE_DARK_OAK));
                m_points.push_back(HullVertex(Math::Vector3(-0.5f, 0.5f, -0.5f), Colours::ROYAL_PURPLE));
                m_points.push_back(HullVertex(Math::Vector3(0.5f, 0.5f, -0.5f), Colours::RED));
                m_points.push_back(HullVertex(Math::Vector3(0.5f, -0.5f, -0.5f), Colours::GREEN));
            }

            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            virtual void CustomGUI()
            {
                Editor::Helper::EditorHelper::DrawVector3Prop("ColliderScale", m_colliderSize);
                Editor::Helper::EditorHelper::DrawVector3Prop("ColliderOffset", m_colliderOffset);
                ColliderComponent::CustomGUI();
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "BoxCollider3DComponent"; }
        };
    }
}