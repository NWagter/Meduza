#pragma once

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <d3d12sdklayers.h>

//DirectX 12 Extention
#pragma warning(push, 0)//disables most external warnings except for ones below
#pragma warning(disable: 26495)
#pragma warning(disable: 26451)
#pragma warning(disable: 4238)
#pragma warning (pop)
#include <d3dx12.h>

// Others
#include <Windows.h>


static const int gs_frameBufferCount = 3;

inline void ThrowIfFailed(HRESULT a_Hr)
{
	if (FAILED(a_Hr))
	{
		throw std::exception();
	}
}


struct Vertex {
	DirectX::XMFLOAT3 pos;
};

struct SubmeshGeometry{

	unsigned int m_indexCount = 0;
	unsigned int m_startIndexLocation = 0;
	int m_vaseVertexLocation = 0;

	DirectX::BoundingBox m_bounds;
};

class Dx12_Mesh;

struct RenderItem {

	RenderItem() = default;

	Dx12_Mesh* m_mesh = nullptr;

	D3D12_PRIMITIVE_TOPOLOGY m_typology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// DrawIndexedInstanced parameters.
	unsigned int m_indexCount = 0;
	unsigned int m_startIndexLocation = 0;
	int m_baseVertexLocation = 0;
};