#pragma once

#include "Platform/General/Editor/EditorRenderer.h"

struct ImGuiContext;
struct ImGuiIO;

namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {
            class RenderLayerDx12;
        }
    }

    namespace Editor
    {
        namespace Dx12
        {
            class EditorRendererDx12 : public Me::Editor::EditorRenderer
            {
                public: 
                    EditorRendererDx12(Renderer::Dx12::RenderLayerDx12*);

                    void Clear() override;
                    void Populate() override;

                private:
                    ImGuiContext* m_imGuiContext;
		            ImGuiIO* m_imguiIO;

                    Renderer::Dx12::RenderLayerDx12* m_renderLayer;
            };
        }
    }
}