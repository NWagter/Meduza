#include "pch/pch.h"
#include "Dx12_CommandList.h"

#include "Dx12_Device.h"

Dx12_CommandList::Dx12_CommandList(D3D12_COMMAND_LIST_TYPE a_type, const Dx12_Device& a_device, int a_w, int a_h)
{
	for (int i = 0; i < gs_frameBufferCount; i++)
	{
		m_cmdAllocator[i] = CreateAlloc(a_device, a_type);
	}


	ThrowIfFailed(a_device.m_device->CreateCommandList(
		0,
		a_type,
		m_cmdAllocator->Get(),
		nullptr,
		IID_PPV_ARGS(m_commandList.GetAddressOf())));

	SetViewAndScissor(a_w, a_h);
}
void Dx12_CommandList::Close()
{
	m_commandList->Close();
}
// uint32_t a_vertexCount, uint32_t a_instanceCount, uint32_t a_startVertex, uint32_t a_startInstance
void Dx12_CommandList::Draw(uint32_t, uint32_t, uint32_t, uint32_t)
{
}
// uint32_t a_indexCount, uint32_t a_instanceCount, uint32_t a_startIndex, int32_t a_baseVertex, uint32_t a_startInstance
void Dx12_CommandList::DrawIndexed(uint32_t , uint32_t , uint32_t , int32_t , uint32_t )
{
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Dx12_CommandList::GetCurrentAllocator(int a_id)
{
	return m_cmdAllocator[a_id];
}

ID3D12GraphicsCommandList* Dx12_CommandList::GetList()
{
	return m_commandList.Get();
}

void Dx12_CommandList::SetViewPort(int a_numViewport)
{
	m_commandList->RSSetViewports(a_numViewport, &m_viewport);
	m_commandList->RSSetScissorRects(a_numViewport, &m_scissorRect);
}

void Dx12_CommandList::SetViewAndScissor(int a_w, int a_h)
{
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(a_w);
	vp.Height = static_cast<float>(a_h);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_viewport = vp;

	m_scissorRect = { 0,0, a_w, a_h };
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Dx12_CommandList::CreateAlloc(const Dx12_Device& a_device, D3D12_COMMAND_LIST_TYPE a_type)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	ThrowIfFailed(a_device.m_device->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator)));

	return commandAllocator;
}
