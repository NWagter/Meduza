#include "mePch.h"

#include "Platform/Windows/DirectX12/Gfx/DX12_Swapchain.h"

#include "Platform/Windows/WinWindow.h"

#include "Platform/Windows/DirectX12/Gfx/DX12_Device.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_CommandQueue.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_Descriptor.h"

mr::DX12_Swapchain::DX12_Swapchain(DX12_Device& a_device, WinWindow& a_window, DX12_CommandQueue& a_queue)
{
	m_device = &a_device;
	m_window = &a_window;
	m_hwnd = a_window.GetHWND();
	m_queue = &a_queue;

	m_currentframeBufferIndex = 0;

	CreateSwapChain();
}

mr::DX12_Swapchain::~DX12_Swapchain()
{
	m_swapChain.ReleaseAndGetAddressOf();
	m_frameBuffer->ReleaseAndGetAddressOf();
}

void mr::DX12_Swapchain::ClearRTV()
{
	m_queue->Flush();

	for (auto& buffer : m_frameBuffer)
	{
		buffer.Reset();
	}
}

void mr::DX12_Swapchain::CreateRTV(DX12_Descriptor& a_descriptor)
{
	auto device = m_device->GetDevice();

	auto rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(a_descriptor.GetHeap()->GetCPUDescriptorHandleForHeapStart());

	int i = 0;
	for (auto& buffer : m_frameBuffer)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> backBuffer;
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer));

		device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);

		buffer = backBuffer;

		rtvHandle.Offset(rtvDescriptorSize);
		i++;
	}
}

void mr::DX12_Swapchain::Resize(int a_w, int a_h)
{
	DXGI_SWAP_CHAIN_DESC1 sd;
	m_swapChain->GetDesc1(&sd);
	m_swapChain.Reset();
	sd.Width = a_w;
	sd.Height = a_h;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	m_device->GetFactory()->CreateSwapChainForHwnd(
		m_queue->GetQueue(),
		m_hwnd,
		&sd,
		nullptr,
		nullptr,
		&swapChain1);

	m_device->GetFactory()->MakeWindowAssociation(m_hwnd, DXGI_MWA_NO_ALT_ENTER);
	swapChain1.As(&m_swapChain);

	m_currentframeBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void mr::DX12_Swapchain::Present()
{
	m_swapChain->Present(0, 0);

	m_currentframeBufferIndex = (m_currentframeBufferIndex + 1) % gs_framebufferCount;

	m_queue->Flush();

}

void mr::DX12_Swapchain::CreateSwapChain()
{
	m_swapChain.Reset();

	RECT rect;
	::GetClientRect(m_window->GetHWND(), &rect);

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = static_cast<int>(rect.right - rect.left);
	swapChainDesc.Height = static_cast<int>(rect.bottom - rect.top);
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc = { 1, 0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = gs_framebufferCount;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	m_device->GetFactory()->CreateSwapChainForHwnd(
		m_queue->GetQueue(),
		m_hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1);

	m_device->GetFactory()->MakeWindowAssociation(m_hwnd, DXGI_MWA_NO_ALT_ENTER);
	swapChain1.As(&m_swapChain);

	m_currentframeBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
}
