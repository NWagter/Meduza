#include "MePCH.h"

#include "Platform/General/Editor/EditorRenderer.h"
#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/Editor/EditorRendererGL.h"
#include "Platform/General/Graphics/RenderLayerGL.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Editor/EditorRendererDx12.h"
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
            return new Dx12::EditorRendererDx12(static_cast<Renderer::Dx12::RenderLayerDx12*>(a_renderLayer));
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
            return new Dx12::EditorRendererDx12(static_cast<Renderer::Dx12::RenderLayerDx12*>(a_renderLayer));
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
}

void Me::Editor::EditorRenderer::AddWidget(EditorWidget& a_widget)
{
    m_editorWidgets.push_back(&a_widget);
}