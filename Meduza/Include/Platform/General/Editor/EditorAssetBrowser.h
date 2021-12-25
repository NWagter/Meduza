#pragma once

#include "Platform/General/Editor/EditorWidget.h"
#include "Platform/Windows/FileSystem/FileSystem.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    struct File
    {
        std::string m_path;
        std::string m_fileName;
    };

    namespace Editor
    {
        class EditorAssetBrowser : public EditorWidget
        {
        public:
            EditorAssetBrowser();
            ~EditorAssetBrowser();

            void Update(float a_dt) override;
            void Draw() override;

        private:
            std::unordered_map<uint8_t, bool> m_filter; 
            std::string m_browserPath;
            Files::BrowseData m_browserData;
        };
    }
}