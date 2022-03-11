#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Components/ColliderComponent.h"

namespace Me
{
    namespace Physics
    {
        struct BoxCollider2DComponent : public ColliderComponent
        {
            Math::Vec2 m_colliderSize = Math::Vec2(1,1);
            Math::Vec2 m_colliderOffset = Math::Vec2(0,0);
            std::vector<Math::Vec3> m_points;

            ComponentID GetColliderComponentID() override
            {
                return s_componentID;
            }

            Math::Vec3 GetFurthestPointInDirection(Math::Vec3 const& a_direction) const override
            {
                Math::Vec2 point(PhysicsHelper::GetFurthestPointInDirection(a_direction, m_points));

                point *= m_colliderSize;
                point += m_colliderOffset;

                return Math::Vec3(point.m_x,point.m_y, 0);
            }

            BoxCollider2DComponent()
            {
                m_points.push_back(Math::Vec3(-0.5f, 0.5f, 0));
                m_points.push_back(Math::Vec3(0.5f, 0.5f, 0));
                m_points.push_back(Math::Vec3(0.5f, -0.5f, 0));
                m_points.push_back(Math::Vec3(-0.5f, -0.5f, 0));
            }
            
            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            virtual void CustomGUI() 
            {
                Editor::Helper::EditorHelper::DrawVec2Prop("ColliderScale", m_colliderSize);
                Editor::Helper::EditorHelper::DrawVec2Prop("ColliderOffset", m_colliderOffset);
                ColliderComponent::CustomGUI();
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "BoxCollider2DComponent"; }
        };
    }
}