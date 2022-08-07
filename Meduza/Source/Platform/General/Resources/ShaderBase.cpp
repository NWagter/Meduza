#include "MePCH.h"
#include "Platform/General/Resources/ShaderBase.h"

#include "Platform/General/FileSystem/FileSystem.h"
#include "Platform/General/Graphics/RenderLayerGL.h"
#include "Platform/General/Resources/Shader.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#elif PLATFORM_LINUX

#elif PLATFORM_APPLE

#endif

Me::Resources::ShaderBase::~ShaderBase()
{

}

Me::Resources::ShaderBase* Me::Resources::ShaderBase::OnCreate(const std::string& a_path)
{
	std::string path = a_path;
	std::string ext = Files::FileSystem::GetFileExtention(path);

	GFX_API api = Renderer::RenderLayer::GetAPI();

	switch (api)
	{
	case GFX_API::DX12:
#ifdef PLATFORM_WINDOWS
		if (ext != "hlsl")
		{
			ME_GFX_LOG("We can't load %s ,\n with the following extention : %s \n", a_path.c_str(), ext.c_str());

			size_t lastindex = path.find_last_of(".");
			path = path.substr(0, lastindex);
			path.append(".hlsl");

			std::ifstream tryPath(path);

			if (!tryPath.is_open())
			{
				return nullptr;
			}

			tryPath.close();
		}
		ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
		return nullptr;
#else
		ME_CORE_ASSERT_M(false, "Platform doesn't support DX12!")
#endif
		break;
	case GFX_API::OpenGL:
		if (ext != "glsl")
		{
			ME_GFX_LOG("We can't load %s ,\n with the following extention : %s \n", a_path.c_str(), ext.c_str());

			size_t lastindex = path.find_last_of(".");
			path = path.substr(0, lastindex);
			path.append(".glsl");

			std::ifstream tryPath(path);

			if (!tryPath.is_open())
			{
				return nullptr;
			}

			tryPath.close();
		}

		return new GL::Shader(path);
		break;
	case GFX_API::Unknown:
#ifdef PLATFORM_WINDOWS
		if (ext != "hlsl")
		{
			ME_GFX_LOG("We can't load %s ,\n with the following extention : %s \n", a_path.c_str(), ext.c_str());
			return nullptr;
		}

		ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
		return nullptr;
#elif PLATFORM_LINUX
		if (ext != "glsl")
		{
			ME_GFX_LOG("We can't load %s ,\n with the following extention : %s \n", path.c_str(), ext.c_str());
			return nullptr;
		}

		return new GL::Shader(path);
#endif
		break;
	}

	return nullptr;
}