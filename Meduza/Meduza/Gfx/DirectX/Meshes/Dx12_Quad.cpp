#include "pch/pch.h"
#include "Dx12_Quad.h"


Dx12_Quad::Dx12_Quad(MeshType a_id, const Dx12_Device& a_device, Dx12_CommandList* a_cmdList) : Dx12_Mesh(a_id)
{
	m_vertices = {
		Vertex(-0.5f,  0.5f, 0.0f), // top left
		Vertex(0.5f, -0.5f, 0.0f), // bottom right
		Vertex(-0.5f, -0.5f, 0.0f), // bottom left  
		Vertex(0.5f,  0.5f, 0.0f),  // top right
	};

	m_indices = {
		0, 1, 2, // first triangle
		0, 3, 1, // second triangle

	};

	InitilizeMesh(a_device, a_cmdList);
}
