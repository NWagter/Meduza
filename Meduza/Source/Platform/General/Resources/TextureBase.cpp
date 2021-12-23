#include "MePCH.h"
#include "Platform/General/Resources/TextureBase.h"

#include "Platform/General/Resources/Texture.h"
#include "Platform/General/Graphics/RenderLayerGL.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include "Platform/Windows/Resources/Texture.h"
#elif PLATFORM_LINUX

#elif PLATFORM_APPLE

#endif

Me::Resources::TextureBase::TextureBase(Math::Vec2 const& a_size) : ResourceBase(ResourceType::Texture)
{
    m_size = a_size;
}

Me::Resources::TextureBase::~TextureBase()
{

}

Me::Resources::TextureBase* Me::Resources::TextureBase::OnCreate(std::string const& a_path)
{
    GFX_API api = Renderer::RenderLayer::GetAPI();

    switch (api)
    {
    case GFX_API::DX12:
    {
#ifdef PLATFORM_WINDOWS
        return dynamic_cast<Renderer::Dx12::RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->LoadTexture(a_path);
#else
        ME_CORE_ASSERT_M(false, "Platform doesn't support DX12!")
#endif
    }
    break;
    case GFX_API::OpenGL:
    {
        return new GL::Texture(a_path);
    }
    break;
    case GFX_API::Unknown:
    {
#ifdef PLATFORM_WINDOWS
        return dynamic_cast<Renderer::Dx12::RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->LoadTexture(a_path);
#elif PLATFORM_LINUX
        return new GL::Texture(a_path);
#endif
    }
    break;
    }
}

Me::Resources::TextureBase* Me::Resources::TextureBase::Create(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height)
{
    GFX_API api = Renderer::RenderLayer::GetAPI();

    switch (api)
    {
    case GFX_API::DX12:
    {
#ifdef PLATFORM_WINDOWS
        return dynamic_cast<Renderer::Dx12::RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->LoadTexture(a_texture, a_width, a_height);
#else
        ME_CORE_ASSERT_M(false, "Platform doesn't support DX12!")
#endif
    }
    break;
    case GFX_API::OpenGL:
    {
        return new GL::Texture(a_texture, a_width, a_height);
    }
    break;
    case GFX_API::Unknown:
    {
#ifdef PLATFORM_WINDOWS
        return dynamic_cast<Renderer::Dx12::RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->LoadTexture(a_texture, a_width, a_height);
#elif PLATFORM_LINUX
        return new GL::Texture(a_texture, a_width, a_height);
#endif
    }
    break;
    }
}