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

    namespace Resources
    {
        class TextureBase;
    }

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
            void LoadIcons();
            std::unordered_map<uint8_t, bool> m_filter; 
            std::string m_browserPath;
            Files::BrowseData m_browserData;
            float m_timer;
            float const m_reloadTime;

            float const m_padding;
            float m_thumbnailSize;

            ImTextureID folderTextureID = 0;
            ImTextureID fileTextureID = 0;
        };
    }
}