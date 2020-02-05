#include "pch/pch.h"
#include "Dx12_RenderLayer.h"

#include "../Window/WinWindow.h"
#include "Dx12_Device.h"
#include "Dx12_Fence.h"
#include "Dx12_Swapchain.h"
#include "Dx12_CommandList.h"
#include "Dx12_CommandQueue.h"
#include "Dx12_Descriptor.h"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

Dx12_RenderLayer::Dx12_RenderLayer(int a_w, int a_h, const char* a_t) {

	CreateNewWindow(a_w,a_h,a_t);

	EnableDebugger();

	m_device = new Dx12_Device();
	m_device->InitDevice();

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	m_cmdQueue = new Dx12_CommandQueue(queueDesc, *m_device);
	m_swapChain = new Dx12_Swapchain(*m_device, static_cast<WinWindow*>(m_window)->GetWindowHandle(), *m_cmdQueue);
	m_swapChain->CreateSwapchain(a_w,a_h);

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = gs_frameBufferCount;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	m_rtv = new Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, desc, *m_device);

	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, srvDesc, *m_device);

	m_swapChain->UpdateRTVView(*m_device, *m_rtv);

	m_cmdList = new Dx12_CommandList(queueDesc.Type, *m_device, a_w, a_h);

	InitImGui();


	m_cmdList->Close();

	m_cmdQueue->Flush();
}

Dx12_RenderLayer::~Dx12_RenderLayer()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	m_cmdQueue->Flush();
}

void Dx12_RenderLayer::Update(float)
{
	m_window->PeekMsg();

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Dx12_RenderLayer::Frame()
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(), m_swapChain->GetCurrentFrameIndex(), m_rtv->GetSize());

	m_cmdList->GetList()->OMSetRenderTargets(1, &rtvHandle, true, nullptr);

	ID3D12DescriptorHeap* descriptorHeaps[] = { m_srv->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_cmdList->GetList());

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_swapChain->GetCurrentBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	m_cmdQueue->ExecuteList(m_cmdList);

	m_swapChain->Present();
}

void Dx12_RenderLayer::Clear(Colour a_colour)
{
	auto commandAllocator = m_cmdList->GetCurrentAllocator(m_swapChain->GetCurrentFrameIndex());
	auto backBuffer = m_swapChain->GetCurrentBuffer();

	commandAllocator->Reset();
	m_cmdList->GetList()->Reset(commandAllocator.Get(), nullptr);

	m_cmdList->SetViewPort(0);

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer.Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	FLOAT clearColor[] = { a_colour.r, a_colour.g, a_colour.b, a_colour.a };

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle (m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_swapChain->GetCurrentFrameIndex(), m_rtv->GetSize());

	m_cmdList->GetList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}

void Dx12_RenderLayer::DestroyLayer()
{
}

void Dx12_RenderLayer::Draw(Drawable)
{
}

void Dx12_RenderLayer::InitImGui()
{
	RenderLayer::InitImGui();

	ImGui_ImplWin32_Init(static_cast<WinWindow*>(m_window)->GetWindowHandle());
	ImGui_ImplDX12_Init(m_device->m_device.Get(), gs_frameBufferCount,
		DXGI_FORMAT_R8G8B8A8_UNORM, m_srv->GetHeap().Get(),
		m_srv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_srv->GetHeap()->GetGPUDescriptorHandleForHeapStart());

	ImGui::StyleColorsDark();
}

void Dx12_RenderLayer::CreateNewWindow(int a_w, int a_h, const char* a_t)
{
	m_window = new WinWindow(a_w, a_h, a_t);
}

void Dx12_RenderLayer::EnableDebugger()
{
#if defined(_DEBUG)
	// Always enable the debug layer before doing anything DX12 related
	// so all possible errors generated while creating DX12 objects
	// are caught by the debug layer.
	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
	debugInterface->EnableDebugLayer();
#endif
}
