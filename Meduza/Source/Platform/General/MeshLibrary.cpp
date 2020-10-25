#include "MePCH.h"
#include "Platform/General/MeshLibrary.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include "Platform/Windows/Resources/Mesh.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/Graphics/RenderLayerGL.h"
#include "Platform/Linux/Resources/Mesh.h"
#elif PLATFORM_APPLE

#endif

Me::Resources::MeshLibrary* Me::Resources::MeshLibrary::ms_instance = nullptr;

Me::Resources::MeshLibrary* Me::Resources::MeshLibrary::CreateMeshLibrary(Renderer::RenderLayer& a_renderer)
{
	if (ms_instance != nullptr)
	{
		ME_GFX_LOG("Mesh Library already Exists!");
		return ms_instance;
	}

	return new MeshLibrary(a_renderer);
}

void Me::Resources::MeshLibrary::Destroy()
{
	delete ms_instance;
}

Me::Resources::MeshLibrary::MeshLibrary(Renderer::RenderLayer& a_renderLayer)
{
    m_renderLayer = &a_renderLayer;

	if (ms_instance != nullptr)
	{
		return;
	}

	ms_instance = this;
}

Me::Resources::MeshLibrary::~MeshLibrary()
{
	for (auto m : ms_instance->m_meshes)
	{
		auto mesh = m.second;
		delete mesh;
	}

	ms_instance->m_meshes.clear();
}

Me::Resources::MeshBase* Me::Resources::MeshLibrary::CreateMesh(std::string a_name)
{
    printf("Couldn't load %s as loading meshes from files is not supported! \n", a_name.c_str());
    return nullptr;
}

Me::Resources::MeshBase* Me::Resources::MeshLibrary::CreateMesh(unsigned int a_id, std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
    if (ms_instance->m_meshes[a_id] != nullptr)
    {
        return GetMesh(a_id);
    }

#ifdef PLATFORM_WINDOWS
	return (static_cast<Renderer::Dx12::RenderLayerDx12*>(ms_instance->m_renderLayer))->CreateMesh(a_vertices, a_indices);
#elif PLATFORM_LINUX
	return (static_cast<Renderer::GL::RenderLayerGL*>(ms_instance->m_renderLayer))->CreateMesh(a_vertices, a_indices);
#elif PLATFORM_APPLE

#endif

    return nullptr;
}

Me::Resources::MeshBase* Me::Resources::MeshLibrary::GetMesh(std::string a_name)
{
	return GetMesh(Utils::Utilities::GetHashedID(a_name));
}

Me::Resources::MeshBase* Me::Resources::MeshLibrary::GetMesh(unsigned int a_id)
{
    //Check if already exists
	if (ms_instance->m_meshes[a_id] == nullptr)
	{
		return nullptr;
	}

	return ms_instance->m_meshes[a_id];
}

bool Me::Resources::MeshLibrary::UnLoadMesh(std::string a_name)
{
    //Check if already exists
	if (!UnLoadMesh(Utils::Utilities::GetHashedID(a_name), false))
	{
		printf("Shader : %s doesn't exist", a_name.c_str());
		return false;
	}
    
	return true;
}

bool Me::Resources::MeshLibrary::UnLoadMesh(unsigned int a_id, bool a_message)
{
	//Check if already exists
	if (ms_instance->m_meshes[a_id] == nullptr)
	{
		if (a_message)
		{
			printf("Shader with ID : %i doesn't exist", a_id);
		}

		return false;
	}

	auto mesh = ms_instance->m_meshes[a_id];
	ms_instance->m_meshes.erase(a_id);
	delete mesh;

	return true;
}