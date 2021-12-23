#include "MePCH.h"
#include "Platform/Windows/Resources/Mesh.h"

#include "Platform/Windows/Helper/Helper.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"


Me::Resources::Dx12::Mesh::Mesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices, Renderer::Dx12::Device& a_device, Renderer::Dx12::CommandList& a_cmd)
	: MeshBase(a_vertices, a_indices)
{
	GenerateBuffers(a_device, a_cmd);
}

Me::Resources::Dx12::Mesh::~Mesh()
{
	m_vertexBufferCPU.ReleaseAndGetAddressOf();
	m_indexBufferCPU.ReleaseAndGetAddressOf();;

	m_vertexBufferGPU.ReleaseAndGetAddressOf();
	m_indexBufferGPU.ReleaseAndGetAddressOf();

	m_vertexBufferUploader.ReleaseAndGetAddressOf();
	m_indexBufferUploader.ReleaseAndGetAddressOf();
}

void Me::Resources::Dx12::Mesh::GenerateBuffers(Renderer::Dx12::Device& a_device, Renderer::Dx12::CommandList& a_cmd)
{
    if(a_cmd.m_closedList || &a_device == nullptr)
    {
        return;
    }

    m_vertexBufferByteSize = sizeof(Vertex) * static_cast<int>(m_vertices.size());
	m_vertexByteStride = sizeof(Vertex);

	m_indexBufferByteSize = sizeof(int) * static_cast<int>(m_indices.size());

	HRESULT hr = S_OK;

	hr = D3DCreateBlob(m_vertexBufferByteSize, &m_vertexBufferCPU);

	if(FAILED(hr))
	{
		ME_GFX_LOG("ERROR! \n");
	}

	m_vertexBufferGPU = Helper::Dx12::Helper::CreateBuffer(a_device.GetDevice(),
		a_cmd.GetList(), m_vertices.data(), m_vertexBufferByteSize, m_vertexBufferUploader);

	m_vertexBufferUploader.Get()->SetName(L"VertexBuffer Uploader");
	m_vertexBufferGPU.Get()->SetName(L"GPU VertexBuffer");

	

	hr = D3DCreateBlob(m_indexBufferByteSize, &m_indexBufferCPU);
	
	if(FAILED(hr))
	{
		ME_GFX_LOG("ERROR! \n");
	}

	m_indexBufferGPU = Helper::Dx12::Helper::CreateBuffer(a_device.GetDevice(),
		a_cmd.GetList(), m_indices.data(), m_indexBufferByteSize, m_indexBufferUploader);

	m_indexBufferUploader.Get()->SetName(L"IndexBuffer Uploader");
	m_indexBufferGPU.Get()->SetName(L"GPU IndexBuffer");

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

void Me::Resources::Dx12::Mesh::DisposeUploaders()
{
	m_vertexBufferUploader = nullptr;
	m_indexBufferUploader = nullptr;
}