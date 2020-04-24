#include "mePch.h"

#include "Core/Resources/Texture.h"


meduza::Texture::Texture(unsigned int a_id) : Resource(a_id)
{

}

meduza::Texture::~Texture()
{

}

void meduza::Texture::LoadResource(std::string a_path)
{
	m_filePath = a_path;
}

void meduza::Texture::UnLoadResource()
{
}

void meduza::Texture::ReloadResource()
{
}
