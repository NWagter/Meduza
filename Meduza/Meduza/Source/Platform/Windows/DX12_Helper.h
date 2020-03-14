#pragma once
#include "Gfx/GFXHelper.h"

namespace cr 
{
	class DX12_Helper
	{
	public:
		static Microsoft::WRL::ComPtr<ID3D12Resource> CreateBuffer(ID3D12Device*,
			ID3D12GraphicsCommandList*,
			const void*,
			UINT64,
			Microsoft::WRL::ComPtr<ID3D12Resource>&);

		static DirectX::XMFLOAT4X4 Identity4x4()
		{
			static DirectX::XMFLOAT4X4 i(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			return i;
		}

		//Convert glm::mat4 to DirectX::XMMATRIX.
		static inline DirectX::XMMATRIX GlmMat4ToDxMat4(const glm::mat4& a_mat4)
		{
			return DirectX::XMMATRIX(
				a_mat4[0][0], a_mat4[0][1], a_mat4[0][2], a_mat4[0][3],
				a_mat4[1][0], a_mat4[1][1], a_mat4[1][2], a_mat4[1][3],
				a_mat4[2][0], a_mat4[2][1], a_mat4[2][2], a_mat4[2][3],
				a_mat4[3][0], a_mat4[3][1], a_mat4[3][2], a_mat4[3][3]
			);
		}

		//Convert glm::vec4 to DirectX::XMFLOAT4.
		static inline DirectX::XMFLOAT4 GlmVec4ToDxFloat4(const glm::vec4& a_vec4)
		{
			return DirectX::XMFLOAT4(
				a_vec4.r,
				a_vec4.g,
				a_vec4.b,
				a_vec4.a
			);
		}
	};

	//Buffer data from big to small.
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4 m_viewProjectionMat = DX12_Helper::Identity4x4();
	};

	struct InstanceBuffer
	{
		DirectX::XMFLOAT4X4 m_modelMat = DX12_Helper::Identity4x4();
		DirectX::XMFLOAT4 m_colour = DirectX::XMFLOAT4(1, 0, 1, 1);
	};

	class DX12_Mesh;

	struct RenderItem 
	{
		RenderItem() = default;
		~RenderItem() = default;

		DX12_Mesh* m_mesh = nullptr;
		DrawType m_drawType;

		D3D12_PRIMITIVE_TOPOLOGY m_typology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

		// DrawIndexedInstanced parameters.
		unsigned int m_startIndexLocation = 0;
		int m_baseVertexLocation = 0;
		int m_shaderId;

		std::vector<InstanceBuffer> m_instances;
		int m_instanceCount = 0;
	};
}