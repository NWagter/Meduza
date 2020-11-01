#include "MePCH.h"
#include "Platform/General/TextureLibrary.h"

#include "Platform/General/FileSystem/FileSystem.h"

Me::Resources::TextureLibrary* Me::Resources::TextureLibrary::ms_instance = nullptr;

Me::Resources::TextureLibrary* Me::Resources::TextureLibrary::CreateTextureLibrary(Renderer::RenderLayer& a_renderLayer)
{
    if(ms_instance != nullptr)
    {
        ME_CORE_LOG("Can't create new Texture Library when there is one already!");
        return ms_instance;
    }

    return new TextureLibrary(a_renderLayer);
}

void Me::Resources::TextureLibrary::Destroy()
{
    delete ms_instance;
}

Me::Texture Me::Resources::TextureLibrary::CreateTexture(std::string a_texture)
{
	std::string ext = Files::FileSystem::GetFileExtention(a_texture);
    Texture hashedId =  Utils::Utilities::GetHashedID(Files::FileSystem::GetFileName(a_texture));

    if (ms_instance->m_textures[hashedId] != nullptr)
    {
        return hashedId;
    }



    return 0;
}

Me::Resources::TextureBase* Me::Resources::TextureLibrary::GetTexture(std::string a_texture)
{
    return GetTexture(Utils::Utilities::GetHashedID(Files::FileSystem::GetFileName(a_texture)));
}
Me::Resources::TextureBase* Me::Resources::TextureLibrary::GetTexture(Me::Texture a_texture)
{
    TextureBase* t = ms_instance->m_textures[a_texture];

    if (t == nullptr)
    {
        ME_CORE_ASSERT_M(false ,"Texture does not exist!");
        return nullptr;
    }

    return t;
}

bool Me::Resources::TextureLibrary::UnloadTexture(std::string a_texture)
{  
    //Check if already exists
	if (!UnloadTexture(Utils::Utilities::GetHashedID(a_texture), false))
	{
		ME_CORE_LOG("Shader : %s doesn't exist", a_texture.c_str());
		return false;
	}
    
	return true;
}
bool Me::Resources::TextureLibrary::UnloadTexture(Texture a_texture, bool a_message)
{
    //Check if already exists
	if (ms_instance->m_textures[a_texture] == nullptr)
	{
		if (a_message)
		{
			ME_CORE_LOG("Shader with ID : %i doesn't exist", a_texture);
		}

		return false;
	}

	auto texture = ms_instance->m_textures[a_texture];
	ms_instance->m_textures.erase(a_texture);
	delete texture;

	return true;
}

Me::Resources::TextureLibrary::TextureLibrary(Renderer::RenderLayer& a_renderLayer)
{
    m_renderLayer = &a_renderLayer;

    if (ms_instance != nullptr)
	{
		return;
	}

	ms_instance = this;
}
Me::Resources::TextureLibrary::~TextureLibrary()
{
    for(auto t : ms_instance->m_textures)
    {
        delete t.second;
    }

	ms_instance->m_textures.clear();
}