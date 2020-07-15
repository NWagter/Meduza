#pragma once

#include "Platform/General/Resources/Mesh.h"

namespace meduza
{
	class MeshDx12 : public Mesh
	{
	public:
		MeshDx12(unsigned int, std::vector<Vertex>, std::vector<int>, VertexAttributes);
		~MeshDx12() override;

		void GenerateBuffers();

		D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;
		D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;

		void DisposeUploaders();

		DXGI_FORMAT m_indexFormat = DXGI_FORMAT_R16_UINT;

		Microsoft::WRL::ComPtr<ID3DBlob> m_vertexBufferCPU = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> m_indexBufferCPU = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBufferGPU = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBufferGPU = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBufferUploader = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBufferUploader = nullptr;

	};
}