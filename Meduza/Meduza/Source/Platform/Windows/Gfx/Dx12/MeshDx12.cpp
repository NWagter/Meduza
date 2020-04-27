#include "mePch.h"

#include "MeduzaUtil.h"

#include "Platform/Windows/Gfx/Dx12/HelperDx12.h"

#include "Platform/Windows/Gfx/Dx12/MeshDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"

meduza::renderer::MeshDx12::MeshDx12(unsigned int a_id, std::vector<Vertex> a_vert, std::vector<int> a_ind, DeviceDx12& a_device, CommandListDx12* a_cmdList) : meduza::renderer::Mesh(a_id, a_vert, a_ind)
{
	m_device = &a_device;
	m_cmd = a_cmdList;

	GenerateBuffers();
}

meduza::renderer::MeshDx12::~MeshDx12()
{
	m_vertexBufferCPU.ReleaseAndGetAddressOf();
	m_indexBufferCPU.ReleaseAndGetAddressOf();;

	m_vertexBufferGPU.ReleaseAndGetAddressOf();
	m_indexBufferGPU.ReleaseAndGetAddressOf();

	m_vertexBufferUploader.ReleaseAndGetAddressOf();
	m_indexBufferUploader.ReleaseAndGetAddressOf();
}

void meduza::renderer::MeshDx12::GenerateBuffers()
{
	if (m_device == nullptr || m_cmd == nullptr)
	{
		assertm(1, "Can't Generate Buffers no context or device available!");
	}

	m_vertexBufferByteSize = sizeof(Vertex) * static_cast<int>(m_vertices.size());
	m_vertexByteStride = sizeof(Vertex);

	m_indexBufferByteSize = sizeof(int) * static_cast<int>(m_indices.size());

	D3DCreateBlob(m_vertexBufferByteSize, &m_vertexBufferCPU);
	CopyMemory(m_vertexBufferCPU->GetBufferPointer(), m_vertices.data(), m_vertexBufferByteSize);

	D3DCreateBlob(m_indexBufferByteSize, &m_indexBufferCPU);
	CopyMemory(m_indexBufferCPU->GetBufferPointer(), m_indices.data(), m_indexBufferByteSize);

	m_vertexBufferGPU = helper::HelperDx12::CreateBuffer(m_device->GetDevice(),
		m_cmd->GetList(), m_vertices.data(), m_vertexBufferByteSize, m_vertexBufferUploader);

	m_indexBufferGPU = helper::HelperDx12::CreateBuffer(m_device->GetDevice(),
		m_cmd->GetList(), m_indices.data(), m_indexBufferByteSize, m_indexBufferUploader);

	m_indexFormat = DXGI_FORMAT_R16_UINT;
}

D3D12_VERTEX_BUFFER_VIEW meduza::renderer::MeshDx12::VertexBufferView() const
{
	if (m_device == nullptr || m_cmd == nullptr)
	{
		assertm(1, "No Buffers available!");
	}

	D3D12_VERTEX_BUFFER_VIEW vBufferView;
	vBufferView.BufferLocation = m_vertexBufferGPU->GetGPUVirtualAddress();
	vBufferView.StrideInBytes = m_vertexByteStride;
	vBufferView.SizeInBytes = m_vertexBufferByteSize;

	return vBufferView;
}

D3D12_INDEX_BUFFER_VIEW meduza::renderer::MeshDx12::IndexBufferView() const
{	
	if (m_device == nullptr || m_cmd == nullptr)
	{
		assertm(1, "No Buffers available!");
	}

	D3D12_INDEX_BUFFER_VIEW indexBufferView;
	indexBufferView.BufferLocation = m_indexBufferGPU->GetGPUVirtualAddress();
	indexBufferView.Format = m_indexFormat;
	indexBufferView.SizeInBytes = m_indexBufferByteSize;

	return indexBufferView;
}

void meduza::renderer::MeshDx12::DisposeUploaders()
{
	m_vertexBufferUploader = nullptr;
	m_indexBufferUploader = nullptr;
}
