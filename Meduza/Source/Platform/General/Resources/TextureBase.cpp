#include "MePCH.h"
#include "Platform/General/Resources/TextureBase.h"

#include "Platform/General/Resources/Texture.h"
#include "Platform/General/Graphics/RenderLayerGL.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#elif PLATFORM_LINUX

#elif PLATFORM_APPLE

#endif

Me::Resources::TextureBase::TextureBase(Math::Vector2 const& a_size) : ResourceBase(ResourceType::Texture)
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
        ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
        return nullptr;
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
        ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
        return nullptr;
#elif PLATFORM_LINUX
        return new GL::Texture(a_path);
#endif
    }
    break;
    }

    return nullptr;
}

Me::Resources::TextureBase* Me::Resources::TextureBase::Create(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height)
{
    GFX_API api = Renderer::RenderLayer::GetAPI();

    switch (api)
    {
    case GFX_API::DX12:
    {
#ifdef PLATFORM_WINDOWS
        ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
        return nullptr;
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
        ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
        return nullptr;
#elif PLATFORM_LINUX
        return new GL::Texture(a_texture, a_width, a_height);
#endif
    }
    break;
    }

    return nullptr;
}