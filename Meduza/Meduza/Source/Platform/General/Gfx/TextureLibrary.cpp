#include "mePch.h"

#include "Core.h"
#include "Platform/General/Utils/MeduzaHelper.h"

#include "Platform/General/Gfx/TextureLibrary.h"

#include "Platform/Windows/Utils/FileSystem.h"

meduza::TextureLibrary* meduza::TextureLibrary::m_instance = nullptr;

meduza::TextureLibrary::TextureLibrary()
{
	if (m_instance != nullptr)
	{
		return;
	}

	m_instance = this;
}

meduza::TextureLibrary::~TextureLibrary()
{
	for (auto s : m_instance->m_textures)
	{
		auto shader = s.second;
		delete shader;
	}

	m_instance->m_textures.clear();
}

meduza::Texture* meduza::TextureLibrary::LoadTexture(std::string a_path)
{
	std::string name = utils::FileSystem::GetFileName(a_path);
	unsigned int hashedId = utils::GetHashedID(name);

	if (m_instance->m_textures[hashedId] != nullptr)
	{
		ME_GFX_LOG("Use Texture %s \n", name.c_str());
		return m_instance->m_textures[hashedId];
	}

	Texture* texture = Texture2D::Create(a_path, hashedId);

	if (texture == nullptr)
	{
		ME_GFX_LOG("Could not Load Texture!");
		return nullptr;
	}


	m_instance->m_textures[hashedId] = texture;

	return texture;
}

meduza::Texture* meduza::TextureLibrary::GetTexture(std::string a_name)
{
	return GetTexture(utils::GetHashedID(a_name));
}

meduza::Texture* meduza::TextureLibrary::GetTexture(unsigned int a_id)
{
	if (m_instance->m_textures[a_id] == nullptr)
	{
		ME_GFX_LOG("Texture with ID : %i doesn't exist", a_id);
		return nullptr;
	}

	auto texture = m_instance->m_textures[a_id];

	return texture;
}

bool meduza::TextureLibrary::UnLoadTexture(std::string a_name)
{
	return UnLoadTexture(utils::GetHashedID(a_name));
}

bool meduza::TextureLibrary::UnLoadTexture(unsigned int a_id, bool a_message)
{
	if (m_instance->m_textures[a_id] == nullptr)
	{
		if (a_message)
		{
			ME_GFX_LOG("Shader with ID : %i doesn't exist", a_id);
		}
	}

	auto texture = m_instance->m_textures[a_id];
	m_instance->m_textures.erase(a_id);
	delete texture;

	return false;
}
