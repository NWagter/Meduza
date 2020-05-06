#include "mePch.h"

#include "Core.h"

#include "Platform/Windows/Resources/OpenGL/TextureGL.h"

#include <Glad/glad.h>
#include <stb_image/stb_image.h>
#include "Platform/Windows/Utils/FileSystem.h"

meduza::Texture2DGL::Texture2DGL(std::string a_path, unsigned int a_id) : m_textureId(a_id)
{
	int width;
	int height;
	int channels;
	stbi_set_flip_vertically_on_load(0);
	stbi_uc* data = stbi_load(a_path.c_str(), &width, &height, &channels, 0);
	ME_GFX_ASSERT_M(data, "Failed to load Texture");
	ME_GFX_LOG("Load texture : %s \n", utils::FileSystem::GetFileName(a_path).c_str());
	m_width = width;
	m_height = height;

	unsigned int formatInternal = 0;
	unsigned int format = 0;

	if (channels == 3)
	{
		formatInternal = GL_RGB8;
		format = GL_RGB;
	}
	else if (channels == 4)
	{
		formatInternal = GL_RGBA8;
		format = GL_RGBA;
	}
	else
	{
		ME_GFX_ASSERT_M(1, "Channel : %i not supported!", channels);
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
	glTextureStorage2D(m_texture, 1, formatInternal, m_width, m_height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTextureSubImage2D(m_texture, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}

meduza::Texture2DGL::~Texture2DGL()
{
	glDeleteTextures(1, &m_texture);
}

void meduza::Texture2DGL::Bind(unsigned int a_slot)
{
	glBindTextureUnit(a_slot, m_texture);
}
