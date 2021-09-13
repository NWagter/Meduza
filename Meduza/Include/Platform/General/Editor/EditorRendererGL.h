#pragma once

#include "Platform/General/Editor/EditorRenderer.h"

struct ImGuiIO;

namespace Me
{
    namespace Renderer
    {
        namespace GL
        {
            class RenderLayerGL;
        }
    }

    namespace Editor
    {
        namespace GL
        {
            class EditorRendererGL : public Me::Editor::EditorRenderer
            {
                public:
                    EditorRendererGL(Renderer::GL::RenderLayerGL*);

                    void Clear() override;
                    void Populate() override;

                private:
                    ImGuiIO* m_imguiIO;
                    Renderer::GL::RenderLayerGL* m_renderLayer;
            };
        }
    }
}
    