#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
            Math::Vector3 m_translation = Math::Vector3(0,0,0);
            Math::Vector3 m_rotation = Math::Vector3(0,0,0);
            Math::Vector3 m_scale = Math::Vector3(1,1,1);

            Math::Matrix4 m_transform = Math::Matrix4::Identity();
            bool m_isDirty = true;

            static ComponentID s_componentID;

            bool m_isStatic = false;

            //Getting
            Math::Matrix4 GetTransform()
            {
                CalculateTransform();

                return m_transform;
            }
            
            void Reset() override
            {
                m_transform = Math::Matrix4::Identity();
            }
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            void CustomGUI() override
            {
                bool isStatic = m_isStatic;
                ImGui::Checkbox("Static", &isStatic);
                m_isStatic = isStatic;

                m_isDirty |= Editor::Helper::EditorHelper::DrawVector3Prop("Position", m_translation);
                m_isDirty |= Editor::Helper::EditorHelper::DrawVector3Prop("Rotation", m_rotation);
                m_isDirty |= Editor::Helper::EditorHelper::DrawVector3Prop("Scale", m_scale);
            }
#endif
#endif
            void serialize(cereal::XMLOutputArchive& a_archive) override
            {
                a_archive(cereal::make_nvp("Translation", m_translation.m_xyz));
                a_archive(cereal::make_nvp("Rotation", m_rotation.m_xyz));
                a_archive(cereal::make_nvp("Scale", m_scale.m_xyz));
            }

            virtual bool RenderCustomGUI() { return true; }
            bool EditorRemoveable() override { return false; }
            std::string EditorComponentName() override { return "TransformComponent"; }

        private:
            void CalculateTransform()
            {
                m_rotation.m_x = m_rotation.m_x > 360 ? m_rotation.m_x - 360 : m_rotation.m_x < 0 ? m_rotation.m_x + 360 : m_rotation.m_x;
                m_rotation.m_y = m_rotation.m_y > 360 ? m_rotation.m_y - 360 : m_rotation.m_y < 0 ? m_rotation.m_y + 360 : m_rotation.m_y;
                m_rotation.m_z = m_rotation.m_z > 360 ? m_rotation.m_z - 360 : m_rotation.m_z < 0 ? m_rotation.m_z + 360 : m_rotation.m_z;

                m_transform = Math::CreateTransformationMatrix(m_translation, m_rotation, m_scale);
                m_isDirty = false;
            }
    };
}