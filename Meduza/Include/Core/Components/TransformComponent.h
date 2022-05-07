#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
            Math::Vector3 m_translation = Math::Vector3(0,0,0);
            Math::Vector3 m_rotation = Math::Vector3(0,0,0); // Degree
            Math::Vector3 m_scale = Math::Vector3(1,1,1);

            static ComponentID s_componentID;

            bool m_isStatic = false;

            //Getting
            Math::Matrix4 GetTransform() const
            {
                Math::Matrix4 translationMat = Math::Matrix4::Identity();
                translationMat.SetPosition(m_translation);
                
                // Degree to Radian
                Me::Math::Vector3 newRot;
                newRot.m_x = (Me::Math::gs_pi / 180) * m_rotation.m_x;
                newRot.m_y = (Me::Math::gs_pi / 180) * m_rotation.m_y;
                newRot.m_z = (Me::Math::gs_pi / 180) * m_rotation.m_z;

                Math::Matrix4 rotationMat = Math::Matrix4::Identity();
                rotationMat.Rotation(newRot);

                Math::Matrix4 scaleMat = Math::Matrix4::Identity();
                scaleMat.SetScale(m_scale);

                return translationMat * rotationMat * scaleMat;
            }
            
            void Reset() override
            {
                m_translation = Math::Vector3(0,0,0);
                m_rotation = Math::Vector3(0,0,0);
                m_scale = Math::Vector3(0,0,0);
            }
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            void CustomGUI() override
            {
                bool isStatic = m_isStatic;
                ImGui::Checkbox("Static", &isStatic);
                m_isStatic = isStatic;

                Editor::Helper::EditorHelper::DrawVector3Prop("Position", m_translation);
                Editor::Helper::EditorHelper::DrawVector3Prop("Rotation", m_rotation);
                Editor::Helper::EditorHelper::DrawVector3Prop("Scale", m_scale);
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
    };
}