#include "MePCH.h"
#include "Platform/General/Resources/MeshBase.h"
#include "Utils/ResourceLoaderUtils.h"

#include "Platform/General/Graphics/RenderLayerGL.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#endif

Me::Resources::MeshBase::MeshBase()
	: Me::Resources::ResourceBase(ResourceType::Mesh)
{

}

Me::Resources::MeshBase::MeshBase(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
	: Me::Resources::ResourceBase(ResourceType::Mesh)
{
	m_vertices = a_vertices;
	m_indices = a_indices;
}

Me::Resources::MeshBase::~MeshBase()
{
	
}

Me::Resources::MeshBase* Me::Resources::MeshBase::OnCreate(const std::string& a_path)
{
	std::vector<Utils::Resources::MeshPrimitives> meshes;

	if (!Me::Utils::Resources::ResourceLoaderUtils::LoadModel(a_path, meshes))
	{
		ME_ASSERT_M(true, "Can't Find Mesh");
		return nullptr;
	}

	return Create(meshes.at(0).m_vertices, meshes.at(0).m_indices);
}

Me::Resources::MeshBase* Me::Resources::MeshBase::Create(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
	GFX_API api = Renderer::RenderLayer::GetAPI();

	switch (api)
	{
	case GFX_API::DX12:
#ifdef PLATFORM_WINDOWS
		return static_cast<Renderer::Dx12::RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->CreateMesh(a_vertices, a_indices);
#else
		ME_CORE_ASSERT_M(false, "This platform doesn't support DX12!")
#endif
			break;
	case GFX_API::OpenGL:
		return static_cast<Renderer::GL::RenderLayerGL*>(Renderer::RenderLayer::GetRenderLayer())->CreateMesh(a_vertices, a_indices);
		break;
	case GFX_API::Unknown:
#ifdef PLATFORM_WINDOWS
		return static_cast<Renderer::Dx12::RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->CreateMesh(a_vertices, a_indices);
#elif PLATFORM_LINUX
		return static_cast<Renderer::GL::RenderLayerGL*>(Renderer::RenderLayer::GetRenderLayer())->CreateMesh(a_vertices, a_indices);
#endif
		break;
	}

	return nullptr;
}

