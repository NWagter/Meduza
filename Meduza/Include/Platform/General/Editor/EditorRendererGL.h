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
                    ~EditorRendererGL();

                    void Clear() override;
                    void Populate() override;

                private:
                    ImGuiIO* m_imguiIO;
                    bool m_dockSpace;
                    Math::Vec2 m_viewportSize = { 0.0f, 0.0f };
                    Renderer::GL::RenderLayerGL* m_renderLayer;
            };
        }
    }
}
    