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
        class EditorResourceBrowser : public EditorWidget
        {
        public:
            EditorResourceBrowser();
            ~EditorResourceBrowser();

            void Update(float) override;
            void Draw() override;
        };
    }
}