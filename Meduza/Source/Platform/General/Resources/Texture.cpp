#include "MePCH.h"

#include "Platform/General/Resources/Texture.h"

#include "Utils/ResourceLoaderUtils.h"

Me::Resources::GL::Texture::Texture(std::string const& a_file) : TextureBase()
{
}

Me::Resources::GL::Texture::Texture(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height) : TextureBase(Math::Vector2(a_width,a_height))
{
    m_textureData = a_texture;
}

Me::Resources::GL::Texture::~Texture()
{

}

void Me::Resources::GL::Texture::Load()
{
    if (m_textureData.empty())
    {
        LoadFromFile();
    }
    else
    {
        LoadFromData();
    }
}

void Me::Resources::GL::Texture::Reload()
{

}

void Me::Resources::GL::Texture::Unload()
{

}

void Me::Resources::GL::Texture::Bind(int a_slot)
{
    glActiveTexture(GL_TEXTURE0 + a_slot);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Me::Resources::GL::Texture::UnBind(int a_slot)
{
    glActiveTexture(GL_TEXTURE0 + a_slot);
    glBindTexture(GL_TEXTURE_2D, 0);    
}

void Me::Resources::GL::Texture::LoadFromFile()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = Me::Utils::Resources::ResourceLoaderUtils::LoadImage(m_path, &width, &height, &nrChannels);

    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ME_GFX_ASSERT_M(true, "Failed to load Texture!");
    }

    m_size = Math::Vector2(float(width), float(height));
    Me::Utils::Resources::ResourceLoaderUtils::FreeImage(data);
}

void Me::Resources::GL::Texture::LoadFromData()
{

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_textureData.size() > 0)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.m_x, m_size.m_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ME_GFX_ASSERT_M(true, "Failed to load Texture!");
    }
}