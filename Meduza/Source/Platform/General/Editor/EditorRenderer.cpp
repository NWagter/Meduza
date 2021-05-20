#include "MePch.h"
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
#ifdef PLATFORM_WINDOWS
    return new Dx12::EditorRendererDx12(static_cast<Renderer::Dx12::RenderLayerDx12*>(a_renderLayer));
#elif PLATFORM_LINUX

#elif PLATFORM_APPLE

#endif

    return nullptr;
}