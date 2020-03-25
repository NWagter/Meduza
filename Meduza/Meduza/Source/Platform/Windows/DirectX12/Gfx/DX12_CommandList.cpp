#include "mePch.h"

#include "Platform/Windows/DirectX12/Gfx/DX12_CommandList.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_Device.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_PipelineStateObject.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_SignatureRoot.h"

mr::DX12_CommandList::DX12_CommandList(D3D12_COMMAND_LIST_TYPE a_type, DX12_Device& a_device, int a_w, int a_h)
{
	for (auto& i : m_cmdAllocator)
	{
		i = CreateAlloc(a_device, a_type);
	}


	a_device.GetDevice()->CreateCommandList(
		0,
		a_type,
		m_cmdAllocator->Get(),
		nullptr,
		IID_PPV_ARGS(m_cmdList.GetAddressOf()));

	SetViewAndScissor(a_w, a_h);
}

mr::DX12_CommandList::~DX12_CommandList()
{
	m_cmdList.ReleaseAndGetAddressOf();
	m_cmdAllocator->ReleaseAndGetAddressOf();
}

void mr::DX12_CommandList::Close()
{
	m_cmdList->Close();
}

void mr::DX12_CommandList::Reset(int a_frame, DX12_PipelineStateObject*)
{
	GetList()->Reset(m_cmdAllocator[a_frame].Get(), nullptr);
}

void mr::DX12_CommandList::Draw(RenderItem*, ID3D12Resource*)
{
}

void mr::DX12_CommandList::SetViewPort(int a_vp)
{
	m_cmdList->RSSetViewports(a_vp, &m_viewport);
	m_cmdList->RSSetScissorRects(a_vp, &m_scissorRect);
}

void mr::DX12_CommandList::SetViewAndScissor(int a_w, int a_h)
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

void mr::DX12_CommandList::SetPSO(DX12_PipelineStateObject*)
{
	m_cmdList->SetPipelineState(nullptr);
}

void mr::DX12_CommandList::SetSignature(DX12_SignatureRoot*)
{
	m_cmdList->SetGraphicsRootSignature(nullptr);
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mr::DX12_CommandList::GetCurrentAllocator(int a_id)
{
	return m_cmdAllocator[a_id];
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mr::DX12_CommandList::CreateAlloc(DX12_Device& a_device, D3D12_COMMAND_LIST_TYPE a_type)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	a_device.GetDevice()->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator));

	return commandAllocator;
}
