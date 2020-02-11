#include "pch/pch.h"
#include "Dx12_Triangle.h"

Dx12_Triangle::Dx12_Triangle(MeshType a_id, const Dx12_Device& a_device, Dx12_CommandList* a_cmdList) : Dx12_Mesh(a_id)
{
	m_vertices = {
		Vertex(0.0f, 0.5f, 0.5f),
		Vertex(0.5f, -0.5f, 0.5f),
		Vertex(-0.5f, -0.5f, 0.5f)
	};

	m_indices = {
		0, 1, 1, 2, 2, 0
	};

	InitilizeMesh(a_device, a_cmdList);
}
