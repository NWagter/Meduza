#include "MePCH.h"
#include "Platform/General/Resources/MeshBase.h"

Me::Resources::MeshBase::MeshBase(std::string a_path, std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
	m_vertices = a_vertices;
	m_indices = a_indices;

	m_filePath = a_path;
}

Me::Resources::MeshBase::~MeshBase()
{
	
}

