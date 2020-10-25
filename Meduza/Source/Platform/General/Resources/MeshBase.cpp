#include "MePCH.h"
#include "Platform/General/Resources/MeshBase.h"

Me::Resources::MeshBase::MeshBase(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
	m_vertices = a_vertices;
	m_indices = a_indices;
}

Me::Resources::MeshBase::~MeshBase()
{
	
}

