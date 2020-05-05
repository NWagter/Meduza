#include "mePch.h"

#include "Platform/General/Resources/Mesh.h"

meduza::renderer::Mesh::Mesh(unsigned int a_id, std::vector<Vertex> a_vertices, std::vector<int> a_indices, VertexAttributes a_atts)
{
	m_meshId = a_id;
	m_vertices = a_vertices;
	m_indices = a_indices;
	m_attributes = a_atts;
}
