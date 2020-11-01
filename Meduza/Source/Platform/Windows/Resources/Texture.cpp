#include "MePCH.h"
#include "Platform/Windows/Helper/Helper.h"
#include "Platform/Windows/Resources/Texture.h"

Me::Resources::Dx12::Texture::Texture(unsigned int a_srvId, Helper::Dx12::TextureData& a_texture, const Math::Vec2 a_size) : TextureBase(a_size)
{
    m_srvId = a_srvId;
    m_texture = &a_texture;
}

Me::Resources::Dx12::Texture::~Texture()
{
    delete m_texture;
}

void Me::Resources::Dx12::Texture::Reload()
{

}

void Me::Resources::Dx12::Texture::Unload()
{

}