#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Physics.h"

namespace Me
{
    namespace Physics
    {
        struct PhysicsComponent : public BaseComponent
        {
            std::vector<CollisionData> m_collided;
            std::vector<CollisionData> m_triggered;
            
            Math::Vector3 m_position = Math::Vector3(0,0,0);
            Math::Vector3 m_movement = Math::Vector3(0,0,0);
            Math::Vector3 m_rotation = Math::Vector3(0,0,0);

            Math::Vector3 m_velocity = Math::Vector3(0,0,0);

            float m_bodyMass = 1.0f;
            float m_drag = 1.0f;
            float m_friction = 1.0f;

            bool m_gravity = true;
            bool m_debugHitNormals = false;

            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            virtual void CustomGUI()
            {
                ImGui::Checkbox("Gravity", &m_gravity);
                ImGui::DragFloat("BodyMass", &m_bodyMass);
                ImGui::DragFloat("Drag", &m_drag);
                ImGui::DragFloat("Friction", &m_friction);

                ImGui::Checkbox("Debug Hit Normals", &m_debugHitNormals);
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "PhysicsComponent"; }

        };
    }
}