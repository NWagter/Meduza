#include "MePCH.h"

#include "Platform/General/Editor/EditorRenderer.h"
#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/Editor/EditorRendererGL.h"
#include "Platform/General/Graphics/RenderLayerGL.h"

#include "Platform/General/Editor/EditorWidget.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#elif PLATFORM_LINUX

#elif PLATFORM_APPLE

#endif

Me::Editor::EditorRenderer* Me::Editor::EditorRenderer::CreateEditor(Me::Renderer::RenderLayer* a_renderLayer)
{
    switch(Me::Renderer::RenderLayer::GetAPI())
    {
        case Me::GFX_API::DX12:
#ifdef PLATFORM_WINDOWS
            ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
            return nullptr;
#else
            ME_CORE_ASSERT_M(false, "Can't open a dx12 editor on this platform!")
#endif
            break;
        case Me::GFX_API::OpenGL:
#ifdef PLATFORM_WINDOWS
            return new GL::EditorRendererGL(static_cast<Renderer::GL::RenderLayerGL*>(a_renderLayer));
#else
            return nullptr;
#endif
            break;
        case Me::GFX_API::Unknown:
#ifdef PLATFORM_WINDOWS
            ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
            return nullptr;
#elif PLATFORM_LINUX
            return nullptr;
#elif PLATFORM_APPLE
            return nullptr;
#endif
            break;
    }

    return nullptr;
}

Me::Editor::EditorRenderer::~EditorRenderer()
{
    for(auto widget : m_editorWidgets)
    {
        delete widget;
    }
    m_editorWidgets.clear();
}

void Me::Editor::EditorRenderer::AddWidget(EditorWidget* const a_widget)
{
    m_editorWidgets.push_back(a_widget);
}