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
	
	CreateQuad();
	CreateCube();
	CreateSphere();
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

#pragma region Primives

void Me::Resources::MeshLibrary::CreateQuad()
{
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
}

void Me::Resources::MeshLibrary::CreateCube()
{
	std::vector<Vertex> cubeVertices = 
		{
			// Front
			Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
			Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
			Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
			Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
			// Back
			Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
			Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
			Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
			Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
			// Top
			Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
			Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
			Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
			Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
			// Bot
			Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
			Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
			Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
			Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
			// Left
			Vertex(-0.5f, -0.5f, 0.5f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f),
			Vertex(-0.5f, 0.5f, 0.5f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f),
			Vertex(-0.5f, 0.5f, -0.5f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f),
			Vertex(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f),
			// Right
			Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
			Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
			Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
			Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f)
		};
		
		std::vector<uint16_t> cubeIndices = 
		{
			// front face
			0, 1, 2, // first triangle
			0, 2, 3, // second triangle

			// Back face
			4, 5, 6, // first triangle
			4, 6, 7, // second triangle

			// Top face
			8, 9, 10, // first triangle
			8, 10, 11, // second triangle

			// Bot face
			12, 13, 14, // first triangle
			12, 14, 15, // second triangle

			// Left face
			16, 17, 18, // first triangle
			16, 18, 19, // second triangle

			// Right face
			20, 21, 22, // first triangle
			20, 22, 23, // second triangle
		};
		
		uint16_t cubeId = static_cast<uint16_t>(Primitives::Cube);
		Resources::MeshLibrary::CreateMesh(cubeId, cubeVertices, cubeIndices);
}

void Me::Resources::MeshLibrary::CreateSphere()
{
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	float radius = 0.5f;
	uint16_t sliceCount = 20;
	uint16_t stackCount = sliceCount;

	Vertex topVertex;
	Me::Math::Vec3 vPos = Me::Math::Vec3(0,radius,0);
	topVertex.m_vertexPos = vPos;
	topVertex.m_normals = vPos.Normalize();
	topVertex.SetUV(0,0);

	Vertex bottomVertex;
	vPos = Me::Math::Vec3(0,-radius,0);
	bottomVertex.m_vertexPos = vPos;
	bottomVertex.m_normals = vPos.Normalize();
	bottomVertex.SetUV(0,1);

	vertices.push_back( topVertex );

	float phiStep   = Math::gs_pi/stackCount;
	float thetaStep = 2.0f*Math::gs_pi/sliceCount;

	for(uint16_t i = 1; i <= stackCount-1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
        for(uint16_t j = 0; j <= sliceCount; ++j)
		{
			float theta = j*thetaStep;

			Vertex v;

			// spherical to cartesian
			Math::Vec3 pos;
			pos.m_x = sinf(phi)*cosf(theta);
			pos.m_y = cosf(phi);
			pos.m_z = sinf(phi)*sinf(theta);

			v.m_normals = pos;
			v.m_vertexPos = pos * radius;

			v.m_uvCoord.m_x = theta / Math::gs_pi2;
			v.m_uvCoord.m_y = phi / Math::gs_pi;

			vertices.push_back( v );
		}
	}

	vertices.push_back(bottomVertex);

    for(uint16_t i = 1; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i+1);
		indices.push_back(i);
	}

    uint16_t baseIndex = 1;
    uint16_t ringVertexCount = sliceCount + 1;
	for(uint16_t i = 0; i < stackCount-2; ++i)
	{
		for(uint16_t j = 0; j < sliceCount; ++j)
		{
			indices.push_back(baseIndex + i*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j+1);
			indices.push_back(baseIndex + (i+1)*ringVertexCount + j);

			indices.push_back(baseIndex + (i+1)*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j+1);
			indices.push_back(baseIndex + (i+1)*ringVertexCount + j+1);
		}
	}


	uint16_t southPoleIndex = (uint16_t)vertices.size()-1;

	baseIndex = southPoleIndex - ringVertexCount;
	
	for(uint16_t i = 0; i < sliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex+i);
		indices.push_back(baseIndex+i+1);
	}

	uint16_t sphereId = static_cast<uint16_t>(Primitives::Sphere);
	Resources::MeshLibrary::CreateMesh(sphereId, vertices, indices);
}

#pragma endregion