#include "pch/pch.h"
#include "Dx12_Swapchain.h"

#include "Dx12_Device.h"
#include "Dx12_CommandQueue.h"
#include "Dx12_Descriptor.h"

Dx12_Swapchain::Dx12_Swapchain(const Dx12_Device& a_device, HWND a_hwnd, Dx12_CommandQueue& a_queue)
{
	m_device = &a_device;
	m_queue = &a_queue;
	m_hwnd = a_hwnd;
	m_currentframeBufferIndex = 0;
}

void Dx12_Swapchain::CreateSwapchain(unsigned int a_width, unsigned int a_height)
{
	m_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = a_width;
	swapChainDesc.Height = a_height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc = { 1, 0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = gs_frameBufferCount;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	ThrowIfFailed(m_device->m_factory->CreateSwapChainForHwnd(
		m_queue->GetQueue(),
		m_hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1));

	ThrowIfFailed(m_device->m_factory->MakeWindowAssociation(m_hwnd, DXGI_MWA_NO_ALT_ENTER));
	ThrowIfFailed(swapChain1.As(&m_swapChain));

	m_currentframeBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
}

Microsoft::WRL::ComPtr<ID3D12Resource> Dx12_Swapchain::GetCurrentBuffer()
{
	return m_swapChainBuffer[m_currentframeBufferIndex];
}

void Dx12_Swapchain::UpdateRTVView(const Dx12_Device& a_device, Dx12_Descriptor& a_descriptor)
{
	auto rtvDescriptorSize = a_device.m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(a_descriptor.GetHeap()->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < gs_frameBufferCount; ++i)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> backBuffer;
		ThrowIfFailed(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));

		a_device.m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);

		m_swapChainBuffer[i] = backBuffer;

		rtvHandle.Offset(rtvDescriptorSize);
	}
}

void Dx12_Swapchain::Present()
{
	ThrowIfFailed(m_swapChain->Present(0, 0));
	
	//Fence with Queue

	m_currentframeBufferIndex = (m_currentframeBufferIndex + 1) % gs_frameBufferCount;
	m_queue->Flush();
}

DXGI_FORMAT Dx12_Swapchain::GetFormat()
{
	return m_backBufferFormat;
}

const HWND Dx12_Swapchain::GetHWND()
{
	return m_hwnd;
}

const unsigned int Dx12_Swapchain::GetCurrentFrameIndex()
{
	return m_currentframeBufferIndex;
}