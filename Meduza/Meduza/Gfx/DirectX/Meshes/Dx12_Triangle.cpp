#include "pch/pch.h"
#include "Dx12_Triangle.h"

#include "../Dx12_Device.h"
#include "../Dx12_CommandList.h"

Dx12_Triangle::Dx12_Triangle(MeshType a_id, const Dx12_Device& a_device, Dx12_CommandList* a_cmdList) : Dx12_Mesh(a_id)
{
	std::vector<Vertex> vList;
	vList.push_back(Vertex(0.0f, 0.5f, 0.5f));
	vList.push_back(Vertex(0.5f, -0.5f, 0.5f));
	vList.push_back(Vertex(-0.5f, -0.5f, 0.5f));

	std::vector<int> indices = {
		0, 1, 1, 2, 2, 0
	};

	m_vertexBufferByteSize = sizeof(Vertex) * static_cast<int>(vList.size());
	m_vertexByteStride = sizeof(Vertex);

	m_indexBufferByteSize = sizeof(int) * static_cast<int>(indices.size());

	D3DCreateBlob(m_vertexBufferByteSize, &m_vertexBufferCPU);
	CopyMemory(m_vertexBufferCPU->GetBufferPointer(), vList.data(), m_vertexBufferByteSize);

	ThrowIfFailed(D3DCreateBlob(m_indexBufferByteSize, &m_indexBufferCPU));
	CopyMemory(m_indexBufferCPU->GetBufferPointer(), indices.data(), m_indexBufferByteSize);

	m_vertexBufferGPU = Dx12Helper::CreateBuffer(a_device.m_device.Get(),
		a_cmdList->GetList(), vList.data(), m_vertexBufferByteSize, m_vertexBufferUploader);

	m_indexBufferGPU = Dx12Helper::CreateBuffer(a_device.m_device.Get(),
		a_cmdList->GetList(), indices.data(), m_indexBufferByteSize, m_indexBufferUploader);

	m_indexFormat = DXGI_FORMAT_R16_UINT;
}
