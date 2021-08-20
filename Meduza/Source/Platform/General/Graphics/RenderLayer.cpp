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

Me::Renderer::RenderLayer* Me::Renderer::RenderLayer::CreateRenderer(Me::Window* a_window, Me::GFX_API a_api)
{
    ms_api = a_api;
    switch (a_api)
    {
        case Me::GFX_API::DX12:
#ifdef PLATFORM_WINDOWS
            return new Dx12::RenderLayerDx12(a_window);
#else
            ME_CORE_ASSERT_M("This platform doesn't support DirectX12")
            return nullptr;
#endif
        break;
        case Me::GFX_API::OpenGL:
            return new GL::RenderLayerGL(a_window);
        break;
        default:
#ifdef PLATFORM_WINDOWS
            return new Dx12::RenderLayerDx12(a_window);
#elif PLATFORM_LINUX
            return new GL::RenderLayerGL(a_window);
#elif PLATFORM_APPLE
            return nullptr;
#endif
        break;
    }
}