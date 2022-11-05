#include "MePCH.h"
#include "Platform/General/Graphics/RenderLayer.h"

#ifdef PLATFORM_WINDOWS

#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include  "Platform/General/Graphics/RenderLayerGL.h"

#elif PLATFORM_LINUX
#include  "Platform/General/Graphics/RenderLayerGL.h"
#elif PLATFORM_APPLE
#endif

Me::GFX_API Me::Renderer::RenderLayer::ms_api = Me::GFX_API::Unknown;
Me::Renderer::RenderLayer* Me::Renderer::RenderLayer::ms_instance = nullptr;
Me::Renderer::RenderLayer* Me::Renderer::RenderLayer::CreateRenderer(Me::Window* a_window, Me::GFX_API a_api)
{
    ms_api = a_api;
    switch (a_api)
    {
        case Me::GFX_API::DX12:
#ifdef PLATFORM_WINDOWS
            ms_instance = new Dx12::RenderLayerDx12(a_window);
            return ms_instance;
#else
            ME_CORE_ASSERT_M(false, "This platform doesn't support DirectX12");
            return nullptr;
#endif
        break;
        case Me::GFX_API::OpenGL:
            ms_instance = new GL::RenderLayerGL(a_window);
            return ms_instance;
        break;
        default:
#ifdef PLATFORM_APPLE
            ME_CORE_ASSERT_M(false, "We don't support Apple :(")
                return nullptr;
#else
            ms_instance = new GL::RenderLayerGL(a_window);
            return ms_instance;
#endif
        break;
    }
}