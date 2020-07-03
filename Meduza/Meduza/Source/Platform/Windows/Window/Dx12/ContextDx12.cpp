#include "mePch.h"

#pragma comment( lib, "d3d12.lib")
#pragma comment( lib, "dxgi.lib")
#pragma comment( lib, "d3dcompiler.lib")
#pragma comment( lib, "dxguid.lib")

#include "Math/MeduzaMath.h"

#include "Platform/Windows/Window/Dx12/ContextDx12.h"

#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandQueueDx12.h"

meduza::renderer::ContextDx12::ContextDx12(HWND a_hwnd)
{

#if defined(MEDUZA_DEBUG)

	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
	debugInterface->EnableDebugLayer();

	Microsoft::WRL::ComPtr<IDXGIDebug> dxgiControler;
	DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiControler));
	dxgiControler->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY));
#endif

	m_device = new DeviceDx12();

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	m_queue = new CommandQueueDx12(queueDesc, *m_device);

	m_hwnd = a_hwnd;

	m_currentframeBufferIndex = 0;

	RECT rect;
	::GetClientRect(a_hwnd, &rect);

	m_size = math::Vec2(float(rect.right - rect.left), float(rect.bottom - rect.top));

	CreateSwapChain();
}

meduza::renderer::ContextDx12::~ContextDx12()
{

	m_frameBuffer->ReleaseAndGetAddressOf();
	m_swapChain.ReleaseAndGetAddressOf();

	m_queue->Flush();
	delete m_queue;

	delete m_device;
}

void meduza::renderer::ContextDx12::SwapBuffer()
{
	m_swapChain->Present(1, 0);

	//Fence with Queue

	m_currentframeBufferIndex = (m_currentframeBufferIndex + 1) % GS_FRAMEBUFFERS;

	m_queue->Flush();

	if (m_resize)
	{
		Resize(m_size);
	}

#if defined(MEDUZA_DEBUG)
	Microsoft::WRL::ComPtr<IDXGIDebug> dxgiControler;
	DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiControler));
	dxgiControler->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY));
#endif
}

void meduza::renderer::ContextDx12::Resize(math::Vec2 a_size)
{
	if (!m_resize)
	{
		m_size = a_size;
		m_resize = true;
		return;
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	m_swapChain.Get()->GetDesc1(&swapChainDesc);

	ClearRTV();

	m_swapChain->ResizeBuffers(GS_FRAMEBUFFERS, int(a_size.m_x), int(a_size.m_y), m_backBufferFormat, swapChainDesc.Flags);


	CreateRTV(*m_rtv);
	m_currentframeBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	m_resize = false;
}

void meduza::renderer::ContextDx12::ClearRTV()
{
	m_queue->Flush();

	for (auto& buffer : m_frameBuffer)
	{
		buffer.Reset();
	}
}

void meduza::renderer::ContextDx12::CreateRTV(DescriptorDx12& a_rtv)
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

void meduza::renderer::ContextDx12::Resize(int a_w, int a_h)
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

void meduza::renderer::ContextDx12::CreateSwapChain()
{
	m_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = int(m_size.m_x);
	swapChainDesc.Height = int(m_size.m_y);
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc = { 1, 0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = GS_FRAMEBUFFERS;
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