#include "MePCH.h"
#include "Platform/Windows/Graphics/ContextDx.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/Descriptor.h"
#include "Platform/Windows/Graphics/CommandQueue.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/WindowsWindow.h"

Me::Renderer::Dx12::Context::Context(Window& a_window, Device* a_device) : Me::Renderer::ContextBase(a_window)
{
#if defined(DEBUG)
	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
	debugInterface->EnableDebugLayer();
#endif

    m_hwnd = static_cast<WindowsWindow*>(&a_window)->GetWindowHandle();
    m_device = a_device;

    m_currentframeBufferIndex = 0;

	RECT rect;
	::GetClientRect(m_hwnd, &rect);


    m_width = float(rect.right - rect.left);
    m_height = float(rect.bottom - rect.top);
}

Me::Renderer::Dx12::Context::~Context()
{
    m_frameBuffer->ReleaseAndGetAddressOf();
	m_swapChain.ReleaseAndGetAddressOf();
	delete m_rtv;
}

void Me::Renderer::Dx12::Context::SwapBuffer(CommandList& a_cmd)
{
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		GetCurrentBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_COMMON);

	a_cmd.GetList()->ResourceBarrier(1, &barrier);

	GetQueue()->ExecuteList(&a_cmd);

	m_swapChain->Present(0, 0);

	//Fence with Queue

	m_currentframeBufferIndex = (m_currentframeBufferIndex + 1) % 3;

	m_queue->Flush();
}

void Me::Renderer::Dx12::Context::Resize(float const a_width, float const a_height)
{
	if (!m_resize)
	{
        m_width = a_width;
        m_height = a_height;
		m_resize = true;
		return;
	}
}

Me::Math::Vec2 Me::Renderer::Dx12::Context::Resize()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	m_swapChain.Get()->GetDesc1(&swapChainDesc);

	ClearRTV();

	m_swapChain->ResizeBuffers(3, int(m_width), int(m_height), m_backBufferFormat, swapChainDesc.Flags);

    //Resize renderer


	CreateRTV(*m_rtv, *m_srv);
	m_currentframeBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	m_resize = false;

	return Math::Vec2(m_width,m_height);
}

void Me::Renderer::Dx12::Context::ClearRTV()
{
	m_queue->Flush();

	for (auto& buffer : m_frameBuffer)
	{
		buffer.Reset();
	}
}

void Me::Renderer::Dx12::Context::CreateRTV(Descriptor& a_rtv, Descriptor& a_srv)
{
	m_rtv = &a_rtv;
	m_srv = &a_srv;

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart());
	CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(m_srv->GetHeap()->GetCPUDescriptorHandleForHeapStart());

	int i = 0;
	for (auto& buffer : m_frameBuffer)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> backBuffer;
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer));

		m_device->GetDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);
		m_device->GetDevice()->CreateShaderResourceView(backBuffer.Get(), nullptr, srvHandle);

		buffer = backBuffer;

		rtvHandle.Offset(m_rtv->GetSize());
		srvHandle.Offset(m_srv->GetSize());
		i++;
	}
}

void Me::Renderer::Dx12::Context::Resize(int const a_width, int const a_height)
{
	DXGI_SWAP_CHAIN_DESC1 sd;
	m_swapChain->GetDesc1(&sd);
	m_swapChain.Reset();
	sd.Width = a_width;
	sd.Height = a_height;

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

void Me::Renderer::Dx12::Context::CreateSwapChain()
{
	m_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = int(m_width);
	swapChainDesc.Height = int(m_height);
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc = { 1, 0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 3;
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

void Me::Renderer::Dx12::Context::CreateSwapchain()
{
	CreateSwapChain();
}

void Me::Renderer::Dx12::Context::SetQueue(CommandQueue& a_queue)
{
    m_queue = &a_queue;
}