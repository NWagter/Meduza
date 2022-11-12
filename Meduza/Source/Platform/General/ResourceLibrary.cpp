#include "MePCH.h"
#include "Platform/General/ResourceLibrary.h"

#include "Platform/General/Resources/MeshBase.h"

Me::Resources::ResourceLibrary* Me::Resources::ResourceLibrary::ms_instance = nullptr;

Me::Resources::ResourceLibrary* Me::Resources::ResourceLibrary::CreateResourceLibrary()
{
	if (ms_instance != nullptr)
	{
		ME_GFX_LOG("ResourceLibrary already Exists!");
		return ms_instance;
	}

	return new ResourceLibrary();
}

Me::Resources::ResourceLibrary* Me::Resources::ResourceLibrary::GetInstance()
{
	if (ms_instance == nullptr)
	{
		ME_ASSERT_M(true, "No Resource Library available!");
	}

	return ms_instance;
}

Me::Resources::ResourceLibrary::ResourceLibrary()
{
	ms_instance = this;

	BaseLoad();
}

void Me::Resources::ResourceLibrary::Cleanup(bool a_baseLoad)
{
	for (auto r : ms_instance->m_resources)
	{
		delete r.second;
	}

	ms_instance->m_resources.clear();

	if (a_baseLoad)
	{
		BaseLoad();
	}
}

void Me::Resources::ResourceLibrary::LoadNewResources()
{
	for (auto r : ms_instance->m_resourceToLoad)
	{
		r->OnLoad();
	}

	ms_instance->m_resourceToLoad.clear();
}

void Me::Resources::ResourceLibrary::BaseLoad()
{
	CreateQuad();
	CreatePlane();
	CreateCube();
	CreateSphere();
}

void Me::Resources::ResourceLibrary::Destroy()
{
	ms_instance->Cleanup(false);

	delete ms_instance;
}

#pragma region Primives
void Me::Resources::ResourceLibrary::CreateQuad()
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

	auto meshBase = MeshBase().Create(quadVertices, quadIndices);	
	meshBase->InitializeResource(quadId, "", "Quad");
	m_resources.insert(std::make_pair(quadId, meshBase));
}

void Me::Resources::ResourceLibrary::CreatePlane()
{
	std::vector<Vertex> planeVertices =
	{
		Vertex(-0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f), // top left,
		Vertex(0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f) ,  // top right
		Vertex(-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), // bottom left 
		Vertex(0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // bottom right 
	};

	std::vector<uint16_t> planeIndices =
	{
		0, 1, 3,
		0, 3, 2
	};

	uint16_t planeId = static_cast<uint16_t>(Primitives::Plane);

	auto meshBase = MeshBase().Create(planeVertices, planeIndices);
	meshBase->InitializeResource(planeId, "", "Plane");
	m_resources.insert(std::make_pair(planeId, meshBase));
}

void Me::Resources::ResourceLibrary::CreateCube()
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

	auto meshBase = MeshBase().Create(cubeVertices, cubeIndices);
	meshBase->InitializeResource(cubeId, "", "Cube");
	m_resources.insert(std::make_pair(cubeId, meshBase));
}

void Me::Resources::ResourceLibrary::CreateSphere()
{
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	float radius = 0.5f;
	uint16_t sliceCount = 20;
	uint16_t stackCount = sliceCount;

	Vertex topVertex;
	Me::Math::Vector3 vPos = Me::Math::Vector3(0, radius, 0);
	topVertex.m_vertexPos = vPos;
	topVertex.m_normals = vPos.Normalize();
	topVertex.SetUV(0, 0);

	Vertex bottomVertex;
	vPos = Me::Math::Vector3(0, -radius, 0);
	bottomVertex.m_vertexPos = vPos;
	bottomVertex.m_normals = vPos.Normalize();
	bottomVertex.SetUV(0, 1);

	vertices.push_back(topVertex);

	float phiStep = Math::gs_pi / stackCount;
	float thetaStep = 2.0f * Math::gs_pi / sliceCount;

	for (uint16_t i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// Vertices of ring.
		for (uint16_t j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex v;

			// spherical to cartesian
			Math::Vector3 pos;
			pos.m_x = sinf(phi) * cosf(theta);
			pos.m_y = cosf(phi);
			pos.m_z = sinf(phi) * sinf(theta);

			v.m_normals = pos;
			v.m_vertexPos = pos * radius;

			v.m_uvCoord.m_x = theta / Math::gs_pi2;
			v.m_uvCoord.m_y = phi / Math::gs_pi;

			vertices.push_back(v);
		}
	}

	vertices.push_back(bottomVertex);

	for (uint16_t i = 1; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	uint16_t baseIndex = 1;
	uint16_t ringVertexCount = sliceCount + 1;
	for (uint16_t i = 0; i < stackCount - 2; ++i)
	{
		for (uint16_t j = 0; j < sliceCount; ++j)
		{
			indices.push_back(baseIndex + i * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}


	uint16_t southPoleIndex = (uint16_t)vertices.size() - 1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (uint16_t i = 0; i < sliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}

	uint16_t sphereId = static_cast<uint16_t>(Primitives::Sphere);

	auto meshBase = MeshBase().Create(vertices, indices);
	meshBase->InitializeResource(sphereId, "", "Sphere");
	m_resources.insert(std::make_pair(sphereId, meshBase));
}
#pragma endregion
