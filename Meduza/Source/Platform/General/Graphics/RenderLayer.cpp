#include "MePCH.h"
#include "Platform/General/Graphics/RenderLayer.h"

#ifdef PLATFORM_WINDOWS

#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include  "Platform/General/Graphics/RenderLayerGL.h"

#elif PLATFORM_LINUX
#include  "Platform/General/Graphics/RenderLayerGL.h"
#elif PLATFORM_APPLE
#endif

Me::Renderer::RenderLayer* Me::Renderer::RenderLayer::CreateRenderer(Me::Window* a_window)
{
#ifdef PLATFORM_WINDOWS
return new Dx12::RenderLayerDx12(a_window);
#elif PLATFORM_LINUX
return new GL::RenderLayerGL(a_window);
#elif PLATFORM_APPLE
return nullptr;
#endif
}