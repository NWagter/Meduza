#pragma once

#include "Platform/General/Resources/Mesh.h"

namespace meduza
{
	class MeshDx12 : public Mesh
	{
	public:
		MeshDx12(unsigned int, std::vector<Vertex>, std::vector<uint16_t>, VertexAttributes);
		~MeshDx12() override;

		void GenerateBuffers() override;

		void DisposeUploaders();

		Microsoft::WRL::ComPtr<ID3DBlob> m_vertexBufferCPU = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> m_indexBufferCPU = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBufferGPU = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBufferGPU = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBufferUploader = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBufferUploader = nullptr;

		D3D12_VERTEX_BUFFER_VIEW GetVertexBuffer() const { return m_vBufferView; };
		D3D12_INDEX_BUFFER_VIEW GetIndexBuffer() const { return m_iBufferView; };

	private:
		DXGI_FORMAT m_indexFormat = DXGI_FORMAT_R32_UINT;

		D3D12_VERTEX_BUFFER_VIEW m_vBufferView;
		D3D12_INDEX_BUFFER_VIEW m_iBufferView;
	};
}