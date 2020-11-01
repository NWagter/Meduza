#include "MePCH.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/FileSystem/FileSystem.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include "Platform/Windows/Resources/Shader.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/Graphics/RenderLayerGL.h"
#include "Platform/Linux/Resources/Shader.h"
#elif PLATFORM_APPLE

#endif

Me::Resources::ShaderLibrary* Me::Resources::ShaderLibrary::ms_instance = nullptr;

Me::Resources::ShaderLibrary* Me::Resources::ShaderLibrary::CreateShaderLibrary(Renderer::RenderLayer& a_renderer)
{
	if (ms_instance != nullptr)
	{
		ME_GFX_LOG("Shader Library already Exists!");
		return ms_instance;
	}

	return new ShaderLibrary(a_renderer);
}

void Me::Resources::ShaderLibrary::Destroy()
{
	delete ms_instance;
}

Me::Resources::ShaderLibrary::ShaderLibrary(Renderer::RenderLayer& a_renderLayer)
{
    m_renderLayer = &a_renderLayer;

	if (ms_instance != nullptr)
	{
		return;
	}

	ms_instance = this;
}

Me::Resources::ShaderLibrary::~ShaderLibrary()
{
	for (auto s : ms_instance->m_shaders)
	{
		auto shader = s.second;
		delete shader;
	}

	ms_instance->m_shaders.clear();
}

Me::Shader Me::Resources::ShaderLibrary::CreateShader(std::string a_path)
{
	std::string ext = Files::FileSystem::GetFileExtention(a_path);

	#ifdef PLATFORM_WINDOWS

	if(ext != "hlsl")
	{
		ME_GFX_LOG("We can't load a file with the following extention : %s \n", ext.c_str());
		return 0;
	}

	Shader hashedId = Utils::Utilities::GetHashedID(Files::FileSystem::GetFileName(a_path));
		if (ms_instance->m_shaders[hashedId] != nullptr)
		{
			return hashedId;
		}

		ms_instance->m_shaders[hashedId] = new Dx12::Shader(a_path,
		 										*dynamic_cast<Renderer::Dx12::RenderLayerDx12*>(ms_instance->m_renderLayer));

		ME_GFX_LOG("Loading of : %s was Succesfull! \n", a_path.c_str());

		return hashedId;//GetShader(hashedId);
	#elif PLATFORM_LINUX
	if(ext != "glsl")
	{
		ME_GFX_LOG("We can't load a file with the following extention : %s \n", ext.c_str());
		return 0;
	}

	Shader hashedId = Utils::Utilities::GetHashedID(Files::FileSystem::GetFileName(a_path));
	if (ms_instance->m_shaders[hashedId] != nullptr)
	{
		return hashedId;
	}

	ms_instance->m_shaders[hashedId] = new GL::Shader(a_path);

	ME_GFX_LOG("Loading of : %s was Succesfull! \n", a_path.c_str());

	return hashedId;
	#elif PLATFORM_APPLE

	#endif
    return 0;
}

Me::Shader Me::Resources::ShaderLibrary::CreateShader(std::string a_vsPath, std::string a_psPath)
{
	std::string ext = Files::FileSystem::GetFileExtention(a_vsPath);
	
	#ifdef PLATFORM_WINDOWS
	if(ext != "hlsl")
	{
		ME_GFX_LOG("We can't load a file with the following extention : %s \n", ext.c_str());
		return 0;
	}
	std::string name = Files::FileSystem::GetFileName(a_vsPath);
	unsigned int hashedId = Utils::Utilities::GetHashedID(Files::FileSystem::GetFileName(a_vsPath));
		if (ms_instance->m_shaders[hashedId] != nullptr)
		{
			return hashedId;
		}

		ms_instance->m_shaders[hashedId] = new Dx12::Shader(a_vsPath, a_psPath,
		 										*dynamic_cast<Renderer::Dx12::RenderLayerDx12*>(ms_instance->m_renderLayer));

		ME_GFX_LOG("Loading of : %s was Succesfull! \n", name.c_str());

		return hashedId;
	#elif PLATFORM_LINUX
	if(ext != "glsl")
	{
		ME_GFX_LOG("We can't load a file with the following extention : %s \n", ext.c_str());
		return 0;
	}

	unsigned int hashedId = Utils::Utilities::GetHashedID(Files::FileSystem::GetFileName(a_vsPath));
	if (ms_instance->m_shaders[hashedId] != nullptr)
	{
		return hashedId;
	}

	ms_instance->m_shaders[hashedId] = new GL::Shader(a_vsPath, a_psPath);

	ME_GFX_LOG("Loading of : %s was Succesfull! \n", a_path.c_str());

	return hashedId;

	#elif PLATFORM_APPLE

	#endif
    return 0;
}

Me::Resources::ShaderBase* Me::Resources::ShaderLibrary::GetShader(std::string a_name)
{
	return GetShader(Utils::Utilities::GetHashedID(a_name));
}

Me::Resources::ShaderBase* Me::Resources::ShaderLibrary::GetShader(Me::Shader a_shader)
{
    //Check if already exists
	if (ms_instance->m_shaders[a_shader] == nullptr)
	{
		ME_GFX_LOG("Shader with id : %i doesn't exist", a_shader);
		return nullptr;
	}

	return ms_instance->m_shaders[a_shader];
}

bool Me::Resources::ShaderLibrary::UnLoadShader(std::string a_name)
{
    //Check if already exists
	if (!UnLoadShader(Utils::Utilities::GetHashedID(a_name), false))
	{
		ME_GFX_LOG("Shader : %s doesn't exist", a_name.c_str());
		return false;
	}
    
	return true;
}

bool Me::Resources::ShaderLibrary::UnLoadShader(Me::Shader a_shader, bool a_message)
{
	//Check if already exists
	if (ms_instance->m_shaders[a_shader] == nullptr)
	{
		if (a_message)
		{
			ME_GFX_LOG("Shader with ID : %i doesn't exist", a_shader);
		}

		return false;
	}

	auto mesh = ms_instance->m_shaders[a_shader];
	ms_instance->m_shaders.erase(a_shader);
	delete mesh;

	return true;
}