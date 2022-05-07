#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
            Math::Vector3 m_translation = Math::Vector3(0,0,0);
            Math::Vector3 m_rotation = Math::Vector3(0,0,0); // Degree
            Math::Vector3 m_scale = Math::Vector3(1,1,1);

            Math::Matrix4 m_transform = Math::Matrix4::Identity();
            bool m_isDirty = true;

            static ComponentID s_componentID;

            bool m_isStatic = false;

            //Getting
            Math::Matrix4 GetTransform()
            {
                if (m_isDirty)
                {
                    CalculateTransform();
                }

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
                a_archive(cereal::make_nvp("Translation", m_transform.GetPosition().m_xyz));
                a_archive(cereal::make_nvp("Rotation", m_transform.GetEuler().m_xyz));
                a_archive(cereal::make_nvp("Scale", m_transform.GetScale().m_xyz));
            }

            virtual bool RenderCustomGUI() { return true; }
            bool EditorRemoveable() override { return false; }
            std::string EditorComponentName() override { return "TransformComponent"; }

        private:
            void CalculateTransform()
            {
                Math::Matrix4 translationMat = Math::Matrix4::Identity();
                translationMat.SetPosition(m_translation);

                Math::Matrix4 rotationMat = Math::Matrix4::Identity();
                rotationMat.Rotation(m_rotation);

                Math::Matrix4 scaleMat = Math::Matrix4::Identity();
                scaleMat.SetScale(m_scale);

                m_transform = translationMat * rotationMat * scaleMat;
                m_isDirty = false;
            }
    };
}