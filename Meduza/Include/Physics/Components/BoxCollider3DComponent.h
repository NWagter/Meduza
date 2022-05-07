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
            std::vector<Math::Vector3> m_points;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }

            Math::Vector3 GetFurthestPointInDirection(Math::Vector3 const& a_direction) const override
            {
                Math::Vector3 point(PhysicsHelper::GetFurthestPointInDirection(a_direction, m_points));

                point *= m_colliderSize;
                point += m_colliderOffset;

                return point;
            }

            BoxCollider3DComponent()
            {
                m_points.push_back(Math::Vector3(-0.5f, 0.5f, 0.5f));
                m_points.push_back(Math::Vector3(0.5f, 0.5f, 0.5f));
                m_points.push_back(Math::Vector3(0.5f, -0.5f, 0.5f));
                m_points.push_back(Math::Vector3(-0.5f, -0.5f, 0.5f));

                m_points.push_back(Math::Vector3(-0.5f, 0.5f, -0.5f));
                m_points.push_back(Math::Vector3(0.5f, 0.5f, -0.5f));
                m_points.push_back(Math::Vector3(0.5f, -0.5f, -0.5f));
                m_points.push_back(Math::Vector3(-0.5f, -0.5f, 0.5f));
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