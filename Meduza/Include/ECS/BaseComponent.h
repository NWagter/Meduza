#pragma once

#include "Core/GUID.h"
#include "EntityTypes.h"
#include "Platform/General/Editor/EditorHelper.h"

#include <imgui.h>
#include <cereal/archives/xml.hpp>

namespace Me
{
    struct BaseComponent
    {
        virtual void Reset(){}
        virtual ~BaseComponent() {}
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
        virtual void CustomGUI() {}
#endif
#endif
        virtual void Serialize(cereal::XMLOutputArchive& a_archive) {}
        virtual bool RenderCustomGUI() { return false; }
        virtual bool EditorRemoveable() { return true; }
        virtual std::string EditorComponentName() { return "Component"; }

        static ComponentID s_componentID;
    };

    struct UIDComponent : public BaseComponent
    {
        UUID m_guid;

        static ComponentID s_componentID;

        void Serialize(cereal::XMLOutputArchive& a_archive) override
        {
            a_archive(cereal::make_nvp("UUID", static_cast<uint32_t>(m_guid)));
        }
    };

    struct TagComponent : public BaseComponent
    {
        std::string m_tag;

        static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
        void CustomGUI() override
        {
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), m_tag.c_str());
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                m_tag = std::string(buffer);
            }
        }
#endif
#endif
        void Serialize(cereal::XMLOutputArchive& a_archive) override
        {
            a_archive(cereal::make_nvp("Tag", m_tag));
        }

        bool EditorRemoveable() override { return false; }
        virtual bool RenderCustomGUI() { return true; }
        std::string EditorComponentName() override { return "TagComponent"; }
    };
    
    struct EditorComponent : public BaseComponent
    {        
        static ComponentID s_componentID;
    };
}