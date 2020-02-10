#include "pch/pch.h"
#include "Dx12_RenderLayer.h"

#include "../Window/WinWindow.h"
#include "Dx12_Device.h"
#include "Dx12_Fence.h"
#include "Dx12_Swapchain.h"
#include "Dx12_CommandList.h"
#include "Dx12_CommandQueue.h"
#include "Dx12_Descriptor.h"
#include "Meshes\Dx12_Triangle.h"

#include "Dx12_PSO.h"
#include "Dx12_RootSignature.h"

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
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, desc, *m_device);

	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, srvDesc, *m_device);

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	m_dsv = new Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, dsvHeapDesc, *m_device);

	ResizeDepthBuffer(a_w,a_h);

	m_swapChain->UpdateRTVView(*m_device, *m_rtv);

	m_cmdList = new Dx12_CommandList(queueDesc.Type, *m_device, a_w, a_h);

	m_signature = new Dx12_RootSignature(*m_device);

	Dx12_PSO* newPso = new Dx12_PSO(0, "Resources\\VertexShader.hlsl", "Resources\\PixelShader.hlsl", *m_device, m_signature);
	m_pipelineStateObjects.push_back(newPso);
	newPso = new Dx12_PSO(0, "Resources\\VertexShader1.hlsl", "Resources\\PixelShader1.hlsl", *m_device, m_signature);
	m_pipelineStateObjects.push_back(newPso);
	newPso = new Dx12_PSO(0, "Resources\\VertexShader2.hlsl", "Resources\\PixelShader2.hlsl", *m_device, m_signature);
	m_pipelineStateObjects.push_back(newPso);
	m_currentPso = m_pipelineStateObjects[0];
	InitImGui();

	MakeTriangle();

	m_cmdQueue->ExecuteList(m_cmdList);

	m_cmdQueue->Flush();
}

void Dx12_RenderLayer::MakeTriangle()
{
	Dx12_Mesh* mesh = new Dx12_Triangle(MeshType::Triangle, *m_device, m_cmdList);
	RenderItem* rItem = new RenderItem();
	rItem->m_mesh = mesh; 
	rItem->m_typology =	D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	rItem->m_indexCount = 3;
	rItem->m_startIndexLocation = 1;
	rItem->m_baseVertexLocation = 1;

	m_renderItems.push_back(rItem);
}

Dx12_RenderLayer::~Dx12_RenderLayer()
{
	m_cmdQueue->Flush();
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX12_Shutdown();
	delete m_device;
	delete m_swapChain;
	delete m_cmdQueue;
	delete m_cmdList;

	delete m_rtv;
	delete m_srv;
	delete m_dsv;
	m_depthBuffer.ReleaseAndGetAddressOf();

	delete m_signature;
	delete m_currentPso;
}

void Dx12_RenderLayer::Update(float a_dt)
{
	if (a_dt == 0) {
		m_currentPso = m_pipelineStateObjects[0];
	}
	else if(a_dt == 1){
		m_currentPso = m_pipelineStateObjects[1];
	}
	else {
		m_currentPso = m_pipelineStateObjects[2];
	}

	m_window->PeekMsg();

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Dx12_RenderLayer::Frame()
{
	ID3D12DescriptorHeap* descriptorHeaps[] = { m_srv->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	m_cmdList->SetPSO(m_currentPso);
	m_cmdList->SetSignature(m_signature);
	m_cmdList->SetViewPort(1);

	for (int i = 0; i < m_renderItems.size(); i++)
	{
		m_cmdList->Draw(m_renderItems[i]);
	}

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
	m_cmdList->Reset(m_swapChain->GetCurrentFrameIndex(), m_currentPso);

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer.Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	FLOAT clearColor[] = { a_colour.r, a_colour.g, a_colour.b, a_colour.a };

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle (m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_swapChain->GetCurrentFrameIndex(), m_rtv->GetSize());

	m_cmdList->GetList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	auto dsv = m_dsv->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	m_cmdList->GetList()->ClearDepthStencilView(dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


	m_cmdList->GetList()->OMSetRenderTargets(1, &rtvHandle, false, &dsv);
}

void Dx12_RenderLayer::DestroyLayer()
{
	delete this;
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

void Dx12_RenderLayer::ResizeDepthBuffer(int a_w, int a_h)
{
	auto device = m_device->m_device;

	// Resize screen dependent resources.
	// Create a depth buffer.
	D3D12_CLEAR_VALUE optimizedClearValue = {};
	optimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	optimizedClearValue.DepthStencil = { 1.0f, 0 };

	CD3DX12_HEAP_PROPERTIES dsvHeap = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC tex = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, a_w, a_h,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	ThrowIfFailed(device->CreateCommittedResource(
		&dsvHeap,
		D3D12_HEAP_FLAG_NONE,
		&tex,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&optimizedClearValue,
		IID_PPV_ARGS(&m_depthBuffer)
	));

	// Update the depth-stencil view.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsv = {};
	dsv.Format = DXGI_FORMAT_D32_FLOAT;
	dsv.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0;
	dsv.Flags = D3D12_DSV_FLAG_NONE;

	device->CreateDepthStencilView(m_depthBuffer.Get(), &dsv,
		m_dsv->GetHeap()->GetCPUDescriptorHandleForHeapStart());
}
