#include "cepch.h"
#include "Platform/Windows/DX12_Mesh.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_CommandList.h"

cr::DX12_Mesh::DX12_Mesh(MeshBuffer a_meshBuffer, cr::DX12_Device& a_device, cr::DX12_CommandList* a_cmdList) : Mesh(a_meshBuffer)
{
	m_vertexBufferByteSize = sizeof(Vertex) * static_cast<int>(m_meshBuffer.m_vertices.size());
	m_vertexByteStride = sizeof(Vertex);

	m_indexBufferByteSize = sizeof(int) * static_cast<int>(m_meshBuffer.m_indices.size());

	D3DCreateBlob(m_vertexBufferByteSize, &m_vertexBufferCPU);
	CopyMemory(m_vertexBufferCPU->GetBufferPointer(), m_meshBuffer.m_vertices.data(), m_vertexBufferByteSize);

	D3DCreateBlob(m_indexBufferByteSize, &m_indexBufferCPU);
	CopyMemory(m_indexBufferCPU->GetBufferPointer(), m_meshBuffer.m_indices.data(), m_indexBufferByteSize);

	m_vertexBufferGPU = DX12_Helper::CreateBuffer(a_device.GetDevice(),
		a_cmdList->GetList(), m_meshBuffer.m_vertices.data(), m_vertexBufferByteSize, m_vertexBufferUploader);

	m_indexBufferGPU = DX12_Helper::CreateBuffer(a_device.GetDevice(),
		a_cmdList->GetList(), m_meshBuffer.m_indices.data(), m_indexBufferByteSize, m_indexBufferUploader);

	m_indexFormat = DXGI_FORMAT_R16_UINT;
}

cr::DX12_Mesh::~DX12_Mesh()
{
	m_vertexBufferCPU.ReleaseAndGetAddressOf();
	m_indexBufferCPU.ReleaseAndGetAddressOf();;

	m_vertexBufferGPU.ReleaseAndGetAddressOf();
	m_indexBufferGPU.ReleaseAndGetAddressOf();

	m_vertexBufferUploader.ReleaseAndGetAddressOf();
	m_indexBufferUploader.ReleaseAndGetAddressOf();
}

D3D12_VERTEX_BUFFER_VIEW cr::DX12_Mesh::VertexBufferView() const
{
	D3D12_VERTEX_BUFFER_VIEW vBufferView;
	vBufferView.BufferLocation = m_vertexBufferGPU->GetGPUVirtualAddress();
	vBufferView.StrideInBytes = m_vertexByteStride;
	vBufferView.SizeInBytes = m_vertexBufferByteSize;

	return vBufferView;
}

D3D12_INDEX_BUFFER_VIEW cr::DX12_Mesh::IndexBufferView() const
{
	D3D12_INDEX_BUFFER_VIEW indexBufferView;
	indexBufferView.BufferLocation = m_indexBufferGPU->GetGPUVirtualAddress();
	indexBufferView.Format = m_indexFormat;
	indexBufferView.SizeInBytes = m_indexBufferByteSize;

	return indexBufferView;
}

void cr::DX12_Mesh::DisposeUploaders()
{
	m_vertexBufferUploader = nullptr;
	m_indexBufferUploader = nullptr;
}
