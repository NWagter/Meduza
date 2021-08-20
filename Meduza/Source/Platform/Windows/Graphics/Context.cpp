#include "MePCH.h"
#include "Platform/Windows/Graphics/Context.h"

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
}

void Me::Renderer::Dx12::Context::SwapBuffers(CommandList& a_cmd)
{
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		GetCurrentBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	a_cmd.GetList()->ResourceBarrier(1, &barrier);

	GetQueue()->ExecuteList(&a_cmd);

	m_swapChain->Present(0, 0);

	//Fence with Queue

	m_currentframeBufferIndex = (m_currentframeBufferIndex + 1) % 3;

	m_queue->Flush();

	if (m_resize)
	{
		Resize(m_width,m_height);
	}
}

void Me::Renderer::Dx12::Context::Resize(float a_x, float a_y)
{
	if (!m_resize)
	{
        m_width = a_x;
        m_width = a_y;
		m_resize = true;
		return;
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	m_swapChain.Get()->GetDesc1(&swapChainDesc);

	ClearRTV();

	m_swapChain->ResizeBuffers(3, int(m_width), int(m_height), m_backBufferFormat, swapChainDesc.Flags);

    //Resize renderer


	CreateRTV(*m_rtv);
	m_currentframeBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	m_resize = false;
}

void Me::Renderer::Dx12::Context::ClearRTV()
{
	m_queue->Flush();

	for (auto& buffer : m_frameBuffer)
	{
		buffer.Reset();
	}
}

void Me::Renderer::Dx12::Context::CreateRTV(Descriptor& a_rtv)
{
	m_rtv = &a_rtv;
	auto rtvDescriptorSize = m_device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart());

	int i = 0;
	for (auto& buffer : m_frameBuffer)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> backBuffer;
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer));

		m_device->GetDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);

		buffer = backBuffer;

		rtvHandle.Offset(rtvDescriptorSize);
		i++;
	}
}

void Me::Renderer::Dx12::Context::Resize(int a_w, int a_h)
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