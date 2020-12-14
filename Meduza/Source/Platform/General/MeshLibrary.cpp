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
	GeneratePrimitives();
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

Me::Mesh Me::Resources::MeshLibrary::CreateMesh(std::string a_name)
{
    printf("Couldn't load %s as loading meshes from files is not supported! \n", a_name.c_str());
    return 0;
}

Me::Mesh Me::Resources::MeshLibrary::CreateMesh(uint16_t a_id, std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
    if (ms_instance->m_meshes[a_id] != nullptr)
    {
        return a_id;
    }

#ifdef PLATFORM_WINDOWS
	ms_instance->m_meshes[a_id] = static_cast<Renderer::Dx12::RenderLayerDx12*>(ms_instance->m_renderLayer)->CreateMesh(a_vertices, a_indices);
	return a_id;
#elif PLATFORM_LINUX
	ms_instance->m_meshes[a_id] = static_cast<Renderer::GL::RenderLayerGL*>(ms_instance->m_renderLayer)->CreateMesh(a_vertices, a_indices);
	return a_id;
#elif PLATFORM_APPLE

#endif

    return 0;
}

Me::Mesh Me::Resources::MeshLibrary::GetMeshIndex(std::string a_name)
{
	return Utils::Utilities::GetHashedID(a_name);
}

Me::Mesh Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives a_primitive)
{
	Mesh meshId = static_cast<uint16_t>(a_primitive);
	return meshId;	
}

Me::Resources::MeshBase* Me::Resources::MeshLibrary::GetMesh(std::string a_name)
{
	return GetMesh(Utils::Utilities::GetHashedID(a_name));
}

Me::Resources::MeshBase* Me::Resources::MeshLibrary::GetMesh(uint16_t a_id)
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
		ME_CORE_LOG("Mesh : %s doesn't exist", a_name.c_str());
		return false;
	}
    
	return true;
}

bool Me::Resources::MeshLibrary::UnLoadMesh(uint16_t a_id, bool a_message)
{
	//Check if already exists
	if (ms_instance->m_meshes[a_id] == nullptr)
	{
		if (a_message)
		{
			ME_CORE_LOG("Mesh with ID : %i doesn't exist", a_id);
		}

		return false;
	}

	auto mesh = ms_instance->m_meshes[a_id];
	ms_instance->m_meshes.erase(a_id);
	delete mesh;

	return true;
}


void Me::Resources::MeshLibrary::GeneratePrimitives()
{
	// Create Quad!
	std::vector<Vertex> quadVertices = 
	{
        Vertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f), // top left,
        Vertex(0.5f,  0.5f, 0.0f, 1.0f, 0.0f) ,  // top right
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f), // bottom left 
        Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f), // bottom right 
    };

	std::vector<uint16_t> quadIndices = 
	{
        0, 1, 3,
        0, 3, 2
    };

	uint16_t quadId = static_cast<uint16_t>(Primitives::Quad);
	Resources::MeshLibrary::CreateMesh(quadId, quadVertices, quadIndices);

	// Create Cube!
	std::vector<Vertex> cubeVertices = 
	{
		// Front
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		// Right
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		// Left
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		// Back
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		// Top
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		// Bot
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f)
    };

	std::vector<uint16_t> cubeIndices = 
	{
		// front face
		0, 1, 2, // first triangle
		0, 3, 1, // second triangle

		// left face
		4, 5, 6, // first triangle
		4, 7, 5, // second triangle

		// right face
		8, 9, 10, // first triangle
		8, 11, 9, // second triangle

		// back face
		12, 13, 14, // first triangle
		12, 15, 13, // second triangle

		// top face
		16, 17, 18, // first triangle
		16, 19, 17, // second triangle

		// bottom face
		20, 21, 22, // first triangle
		20, 23, 21, // second triangle
    };
	
	uint16_t cubeId = static_cast<uint16_t>(Primitives::Cube);
	Resources::MeshLibrary::CreateMesh(cubeId, cubeVertices, cubeIndices);
}