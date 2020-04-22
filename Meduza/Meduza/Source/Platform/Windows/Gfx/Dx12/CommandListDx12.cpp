#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"

meduza::renderer::CommandListDx12::CommandListDx12(D3D12_COMMAND_LIST_TYPE a_type, DeviceDx12& a_device, math::Vec2 a_size)
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

	SetViewAndScissor(a_size);
}

meduza::renderer::CommandListDx12::~CommandListDx12()
{
	m_cmdList.ReleaseAndGetAddressOf();
	m_cmdAllocator->ReleaseAndGetAddressOf();
}

void meduza::renderer::CommandListDx12::Close()
{
	m_cmdList->Close();
}

void meduza::renderer::CommandListDx12::Reset(unsigned int a_frame)
{
	GetList()->Reset(m_cmdAllocator[a_frame].Get(), nullptr);
}

void meduza::renderer::CommandListDx12::SetViewPort(int a_port)
{
	m_cmdList->RSSetViewports(a_port, &m_viewport);
	m_cmdList->RSSetScissorRects(a_port, &m_scissorRect);
}

void meduza::renderer::CommandListDx12::SetViewAndScissor(math::Vec2 a_size)
{
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = a_size.m_x;
	vp.Height = a_size.m_y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_viewport = vp;

	m_scissorRect = { 0,0, int(a_size.m_x), int(a_size.m_y) };
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> meduza::renderer::CommandListDx12::GetCurrentAllocator(unsigned int a_id)
{
	return m_cmdAllocator[a_id];
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> meduza::renderer::CommandListDx12::CreateAlloc(DeviceDx12& a_device, D3D12_COMMAND_LIST_TYPE a_type)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	a_device.GetDevice()->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator));

	return commandAllocator;
}
