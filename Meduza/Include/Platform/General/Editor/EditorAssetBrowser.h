#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
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
            std::unordered_map<uint8_t, bool> m_filter;
        };
    }
}