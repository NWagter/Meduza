#include "pch/pch.h"
#include "Dx12_Mesh.h"

Dx12_Mesh::Dx12_Mesh(int a_id) : Mesh(a_id)
{
}

D3D12_VERTEX_BUFFER_VIEW Dx12_Mesh::VertexBufferView() const
{
		D3D12_VERTEX_BUFFER_VIEW vbv;
		vbv.BufferLocation = m_vertexBufferGPU->GetGPUVirtualAddress();
		vbv.StrideInBytes = m_vertexByteStride;
		vbv.SizeInBytes = m_vertexBufferByteSize;

		return vbv;
}

D3D12_INDEX_BUFFER_VIEW Dx12_Mesh::IndexBufferView() const
{
	D3D12_INDEX_BUFFER_VIEW ibv;
	ibv.BufferLocation = m_indexBufferGPU->GetGPUVirtualAddress();
	ibv.Format = m_indexFormat;
	ibv.SizeInBytes = m_indexBufferByteSize;

	return ibv;
}

void Dx12_Mesh::DisposeUploaders()
{
	m_vertexBufferUploader = nullptr;
	m_indexBufferUploader = nullptr;
}
