#include "MePCH.h"
#include "Platform/Windows/Helper/Helper.h"
#include "Platform/Windows/Resources/Texture.h"

Me::Resources::Dx12::Texture::Texture(unsigned int const a_srvId, Helper::Dx12::TextureData& a_texture, Math::Vec2 const& a_size) : TextureBase(a_size)
{
    m_srvId = a_srvId;
    m_texture = &a_texture;
}

Me::Resources::Dx12::Texture::~Texture()
{
    if (m_texture->m_resource.Get() != nullptr)
        m_texture->m_resource->Release();
    delete m_texture;
}

void Me::Resources::Dx12::Texture::Reload()
{

}

void Me::Resources::Dx12::Texture::Unload()
{

}