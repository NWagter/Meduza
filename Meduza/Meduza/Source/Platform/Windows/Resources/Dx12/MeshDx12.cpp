#include "mePch.h"

#include "Core.h"

#include "Platform/Windows/Utils/Dx12/HelperDx12.h"

#include "Platform/Windows/Resources/Dx12/MeshDx12.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"

meduza::MeshDx12::MeshDx12(unsigned int a_id, std::vector<Vertex> a_vert, std::vector<uint16_t> a_ind, VertexAttributes a_atts) : meduza::Mesh(a_id, a_vert, a_ind, a_atts)
{
	GenerateBuffers();
}

meduza::MeshDx12::~MeshDx12()
{
	m_vertexBufferCPU.ReleaseAndGetAddressOf();
	m_indexBufferCPU.ReleaseAndGetAddressOf();;

	m_vertexBufferGPU.ReleaseAndGetAddressOf();
	m_indexBufferGPU.ReleaseAndGetAddressOf();

	m_vertexBufferUploader.ReleaseAndGetAddressOf();
	m_indexBufferUploader.ReleaseAndGetAddressOf();
}

void meduza::MeshDx12::GenerateBuffers()
{
	auto cmd = &renderer::RendererDx12::GetRenderer()->GetCmd();

	if (cmd->m_closedList)
	{
		return;
	}

	auto device = renderer::RendererDx12::GetRenderer()->GetContext().GetDevice();

	if (device == nullptr || cmd == nullptr)
	{
		ME_GFX_ASSERT_M(0, "Can't Generate Buffers no context or device available!");
	}

	m_vertexBufferByteSize = sizeof(Vertex) * static_cast<int>(m_vertices.size());
	m_vertexByteStride = sizeof(Vertex);

	m_indexBufferByteSize = sizeof(int) * static_cast<int>(m_indices.size());

	D3DCreateBlob(m_vertexBufferByteSize, &m_vertexBufferCPU);
	CopyMemory(m_vertexBufferCPU->GetBufferPointer(), m_vertices.data(), m_vertexBufferByteSize);

	D3DCreateBlob(m_indexBufferByteSize, &m_indexBufferCPU);
	CopyMemory(m_indexBufferCPU->GetBufferPointer(), m_indices.data(), m_indexBufferByteSize);
	
	m_vertexBufferGPU = renderer:: helper::HelperDx12::CreateBuffer(device->GetDevice(),
		cmd->GetList(), m_vertices.data(), m_vertexBufferByteSize, m_vertexBufferUploader);

	m_vertexBufferUploader.Get()->SetName(L"VertexBuffer Uploader");
	m_vertexBufferGPU.Get()->SetName(L"GPU VertexBuffer");

	m_indexBufferGPU = renderer::helper::HelperDx12::CreateBuffer(device->GetDevice(),
		cmd->GetList(), m_indices.data(), m_indexBufferByteSize, m_indexBufferUploader);

	m_vertexBufferUploader.Get()->SetName(L"IndexBuffer Uploader");
	m_vertexBufferGPU.Get()->SetName(L"GPU IndexBuffer");

	m_indexFormat = DXGI_FORMAT_R16_UINT;

	D3D12_VERTEX_BUFFER_VIEW vBufferView;
	vBufferView.BufferLocation = m_vertexBufferGPU->GetGPUVirtualAddress();
	vBufferView.StrideInBytes = m_vertexByteStride;
	vBufferView.SizeInBytes = m_vertexBufferByteSize;

	m_vBufferView = vBufferView;

	D3D12_INDEX_BUFFER_VIEW iBufferView;
	iBufferView.BufferLocation = m_indexBufferGPU->GetGPUVirtualAddress();
	iBufferView.Format = m_indexFormat;
	iBufferView.SizeInBytes = m_indexBufferByteSize;

	m_iBufferView = iBufferView;

}

void meduza::MeshDx12::DisposeUploaders()
{
	m_vertexBufferUploader = nullptr;
	m_indexBufferUploader = nullptr;
}
