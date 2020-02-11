#include "pch/pch.h"
#include "Dx12_Mesh.h"

#include "../Dx12_Device.h"
#include "../Dx12_CommandList.h"

Dx12_Mesh::Dx12_Mesh(MeshType a_id) : Mesh(a_id)
{
}

void Dx12_Mesh::InitilizeMesh(const Dx12_Device& a_device, Dx12_CommandList* a_cmdList)
{
	m_vertexBufferByteSize = sizeof(Vertex) * static_cast<int>(m_vertices.size());
	m_vertexByteStride = sizeof(Vertex);

	m_indexBufferByteSize = sizeof(int) * static_cast<int>(m_indices.size());

	D3DCreateBlob(m_vertexBufferByteSize, &m_vertexBufferCPU);
	CopyMemory(m_vertexBufferCPU->GetBufferPointer(), m_vertices.data(), m_vertexBufferByteSize);

	ThrowIfFailed(D3DCreateBlob(m_indexBufferByteSize, &m_indexBufferCPU));
	CopyMemory(m_indexBufferCPU->GetBufferPointer(), m_indices.data(), m_indexBufferByteSize);

	m_vertexBufferGPU = Dx12Helper::CreateBuffer(a_device.m_device.Get(),
		a_cmdList->GetList(), m_vertices.data(), m_vertexBufferByteSize, m_vertexBufferUploader);

	m_indexBufferGPU = Dx12Helper::CreateBuffer(a_device.m_device.Get(),
		a_cmdList->GetList(), m_indices.data(), m_indexBufferByteSize, m_indexBufferUploader);

	m_indexFormat = DXGI_FORMAT_R16_UINT;
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

int Dx12_Mesh::GetIndexCount()
{
	return static_cast<int>(m_indices.size());
}
