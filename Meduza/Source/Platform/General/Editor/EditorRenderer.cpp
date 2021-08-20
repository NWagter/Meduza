#include "MePCH.h"

#include "Platform/General/Editor/EditorRenderer.h"
#include "Platform/General/Graphics/RenderLayer.h"

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
            ME_CORE_ASSERT_M("Can't open a dx12 editor on this platform!")
#endif
            break;
        case Me::GFX_API::OpenGL:
            return nullptr;
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