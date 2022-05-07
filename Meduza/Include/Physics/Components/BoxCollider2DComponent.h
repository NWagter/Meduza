#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct BoxCollider2DComponent : public ColliderComponent
        {
            Math::Vector2 m_colliderSize = Math::Vector2(1,1);
            Math::Vector2 m_colliderOffset = Math::Vector2(0,0);
            std::vector<Math::Vector3> m_points;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }

            Math::Vector3 GetFurthestPointInDirection(Math::Matrix4 const& a_transform, Math::Vector3 const& a_direction) const override
            {
                Math::Vector2 point(PhysicsHelper::GetFurthestPointInDirection(a_transform, a_direction, m_points));

                point *= m_colliderSize;
                point += m_colliderOffset;

                return Math::Vector3(point.m_x,point.m_y, 0);
            }

            BoxCollider2DComponent()
            {
                m_points.push_back(Math::Vector3(-0.5f, 0.5f, 0));
                m_points.push_back(Math::Vector3(0.5f, 0.5f, 0));
                m_points.push_back(Math::Vector3(0.5f, -0.5f, 0));
                m_points.push_back(Math::Vector3(-0.5f, -0.5f, 0));
            }
            
            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            virtual void CustomGUI() 
            {
                Editor::Helper::EditorHelper::DrawVector2Prop("ColliderScale", m_colliderSize);
                Editor::Helper::EditorHelper::DrawVector2Prop("ColliderOffset", m_colliderOffset);
                ColliderComponent::CustomGUI();
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "BoxCollider2DComponent"; }
        };
    }
}