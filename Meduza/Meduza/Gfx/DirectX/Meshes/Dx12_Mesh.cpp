#include "pch/pch.h"
#include "Dx12_Mesh.h"

Dx12_Mesh::Dx12_Mesh(MeshType a_id) : Mesh(a_id)
{
}

D3D12_VERTEX_BUFFER_VIEW Dx12_Mesh::VertexBufferView() const
{
		D3D12_VERTEX_BUFFER_VIEW vBufferView;
		vBufferView.BufferLocation = m_vertexBufferGPU->GetGPUVirtualAddress();
		vBufferView.StrideInBytes = m_vertexByteStride;
		vBufferView.SizeInBytes = m_vertexBufferByteSize;

		return vBufferView;
}

D3D12_INDEX_BUFFER_VIEW Dx12_Mesh::IndexBufferView() const
{
	D3D12_INDEX_BUFFER_VIEW indexBufferView;
	indexBufferView.BufferLocation = m_indexBufferGPU->GetGPUVirtualAddress();
	indexBufferView.Format = m_indexFormat;
	indexBufferView.SizeInBytes = m_indexBufferByteSize;

	return indexBufferView;
}

void Dx12_Mesh::DisposeUploaders()
{
	m_vertexBufferUploader = nullptr;
	m_indexBufferUploader = nullptr;
}
