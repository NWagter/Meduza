#include "MePCH.h"

#include "Platform/Linux/Resources/Texture.h"

#include "stb_image.h"

Me::Resources::Texture::Texture(std::string a_textureFile)
{
    glGenTextures(1, &m_texture);  
    glBindTexture(GL_TEXTURE_2D, texture);  

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(a_textureFile.cstr(), &width, &height, &nrChannels, 0); 
    if (data)
    {   
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ME_GFX_ASSERT_M(true, "Failed to load Texture!");
    }
    
    stbi_image_free(data);
}

Me::Resources::Texture~Texture()
{

}

void Me::Resources::Texture::Reload()
{

}

void Me::Resources::Texture::Unload()
{

}

void Me::Resources::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Me::Resources::Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);    
}