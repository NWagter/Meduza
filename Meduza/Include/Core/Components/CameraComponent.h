#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    enum class CameraType : int
    {
        Orthographic,
        Perspective
    };

    struct CameraComponent : public BaseComponent
    {
        CameraComponent()
        {            
            m_near = -0.1f;
            m_far = 1000;
            m_orthoScale = 10;
            m_cameraType = CameraType::Orthographic;
            m_cameralayer = 0;
        }
        void Reset() override
        {
            m_near = -0.1f;
            m_far = 1000;
            m_orthoScale = 10;
            m_cameralayer = 0;
        }

        Math::Vec2 m_size;
        float m_orthoScale;
        float m_near;
        float m_far;

        CameraType m_cameraType;
        int m_cameralayer;
        
        static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
        virtual void CustomGUI() 
        {
            const char* projectionStrings[] = { "Orthographic", "Perspective" };
            const char* currentProjectionString = projectionStrings[int(m_cameraType)];

            if (ImGui::BeginCombo("Projection", currentProjectionString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool isSelected = currentProjectionString == projectionStrings[i];

                    if (ImGui::Selectable(projectionStrings[i], isSelected))
                    {
                        currentProjectionString = projectionStrings[i];
                        m_cameraType = CameraType(i);
                    }

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }


                ImGui::EndCombo();
            }

            if (m_cameraType == CameraType::Perspective)
            {
                Editor::Helper::EditorHelper::DrawVec2Prop("Size", m_size);
            }
            else if (m_cameraType == CameraType::Orthographic)
            {
                ImGui::DragFloat("Scale", &m_orthoScale);
            }

            ImGui::DragFloat("Near", &m_near);
            ImGui::DragFloat("Far", &m_far);
            ImGui::DragInt("Camera Layer", &m_cameralayer);
        }
        virtual void serialize(cereal::XMLOutputArchive& a_archive)
        {
            a_archive(cereal::make_nvp("Far", m_far));
            a_archive(cereal::make_nvp("Near", m_near));
            a_archive(cereal::make_nvp("Size", m_size.m_xy));
            a_archive(cereal::make_nvp("OrthoScale", m_orthoScale));
            a_archive(cereal::make_nvp("CameraLayer", m_cameralayer));
            a_archive(cereal::make_nvp("CameraType", (int)m_cameraType));
        }
#endif
#endif
        virtual bool RenderCustomGUI() { return true; }
        std::string EditorComponentName() override { return "CameraComponent"; }
    };
}