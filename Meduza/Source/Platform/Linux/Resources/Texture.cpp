#include "MePCH.h"

#include "Platform/Linux/Resources/Texture.h"

#include "Utils/ResourceLoaderUtils.h"

Me::Resources::GL::Texture::Texture(std::string a_textureFile) : TextureBase(Math::Vec2(0,0))
{
    glGenTextures(1, &m_texture);  
    glBindTexture(GL_TEXTURE_2D, m_texture);  

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = Me::Utils::Resources::ResourceLoaderUtils::LoadImage(a_textureFile, &width, &height, &nrChannels); 

    if (data)
    {   
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ME_GFX_ASSERT_M(true, "Failed to load Texture!");
    }

    m_size = Math::Vec2(float(width), float(height));
    Me::Utils::Resources::ResourceLoaderUtils::FreeImage(data);
}

Me::Resources::GL::Texture::~Texture()
{

}

void Me::Resources::GL::Texture::Reload()
{

}

void Me::Resources::GL::Texture::Unload()
{

}

void Me::Resources::GL::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Me::Resources::GL::Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);    
}