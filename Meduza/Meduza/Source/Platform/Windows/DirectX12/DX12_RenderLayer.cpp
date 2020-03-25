#include "mePch.h"

#include "Platform/Windows/DirectX12/DX12_RenderLayer.h"
#include "Platform/Windows/WinWindow.h"

#include "Platform/Windows/DirectX12/Gfx/DX12_Device.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_Swapchain.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_Descriptor.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_CommandQueue.h"
#include "Platform/Windows/DirectX12/Gfx/DX12_CommandList.h"

#include "optick.h"
#include "optick.config.h"

mr::DX12_Renderlayer::DX12_Renderlayer(Window& a_window)
{
#if defined(_DEBUG)
	EnableDebugLayer();
#endif
	m_window = static_cast<WinWindow*>(&a_window);

	RECT rect;
	::GetClientRect(m_window->GetHWND(), &rect);

	int width = static_cast<int>(rect.right - rect.left);
	int height = static_cast<int>(rect.bottom - rect.top);


	m_device = new DX12_Device();

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	m_cmdQueue = new DX12_CommandQueue(queueDesc, *m_device);
	m_swapChain = new DX12_Swapchain(*m_device, *m_window, *m_cmdQueue);

	m_cmdList = new DX12_CommandList(queueDesc.Type, *m_device, width, height);

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 3;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, desc, *m_device);
	m_swapChain->CreateRTV(*m_rtv);

	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, srvDesc, *m_device);

	D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
	cbvDesc.NumDescriptors = 1;
	cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	for (auto& i : m_cbv)
	{
		i = new DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, cbvDesc, *m_device);
	}

	m_cmdQueue->ExecuteList(m_cmdList);

	m_cmdQueue->Flush();

	ID3D12CommandQueue* cmdQueues[] = { m_cmdQueue->GetQueue() };

	Optick::InitGpuD3D12(m_device->GetDevice(), cmdQueues, 1);
}

mr::DX12_Renderlayer::~DX12_Renderlayer()
{
	m_cmdQueue->Flush();

	delete m_device;
	delete m_swapChain;
	delete m_cmdQueue;
	delete m_cmdList;
	delete m_rtv;
	delete m_srv;
	
	for (auto c : m_cbv)
	{
		delete c;
	}
}

void mr::DX12_Renderlayer::Clear(float a_colour[4])
{
	OPTICK_FRAME("Clear");
	OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Rendering);
	float* cColour = a_colour;
	//Clear the FrameBuffer
	auto commandAllocator = m_cmdList->GetCurrentAllocator(m_swapChain->GetCurrentFrameIndex());
	auto backBuffer = m_swapChain->GetCurrentBuffer();

	commandAllocator->Reset();
	m_cmdList->Reset(m_swapChain->GetCurrentFrameIndex(), nullptr);

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_swapChain->GetCurrentFrameIndex(), m_rtv->GetSize());

	m_cmdList->GetList()->OMSetRenderTargets(1, &rtvHandle, 0, nullptr);

	m_cmdList->GetList()->ClearRenderTargetView(rtvHandle, cColour, 0, nullptr);
}

void mr::DX12_Renderlayer::PreRender()
{
	OPTICK_FRAME("Pre Render");
	OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Rendering);
}

void mr::DX12_Renderlayer::Render()
{
	/*ID3D12DescriptorHeap* cbvDescriptorHeaps[] = { m_cbv[m_swapChain->GetCurrentFrameIndex()]->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(cbvDescriptorHeaps), cbvDescriptorHeaps);*/

	OPTICK_FRAME("Rendering");
	OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Rendering);

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_swapChain->GetCurrentBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	m_cmdQueue->ExecuteList(m_cmdList);

	m_swapChain->Present();
}

void mr::DX12_Renderlayer::Resize()
{
	RECT rect;
	::GetClientRect(m_window->GetHWND(), &rect);
	int w = static_cast<int>(rect.right - rect.left);
	int h = static_cast<int>(rect.bottom - rect.top);

	//ImGui_ImplDX12_InvalidateDeviceObjects();
	m_swapChain->ClearRTV();


	m_swapChain->Resize(w, h);
	m_cmdList->SetViewAndScissor(w, h);
	m_swapChain->CreateRTV(*m_rtv);
	//ImGui_ImplDX12_CreateDeviceObjects();
}

void mr::DX12_Renderlayer::EnableDebugLayer()
{
	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
	debugInterface->EnableDebugLayer();
}
