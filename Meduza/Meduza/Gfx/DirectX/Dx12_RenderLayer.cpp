#include "pch/pch.h"
#include "Dx12_RenderLayer.h"

#include "../Window/WinWindow.h"
#include "Dx12_Device.h"
#include "Dx12_Fence.h"
#include "Dx12_Swapchain.h"
#include "Dx12_CommandList.h"
#include "Dx12_CommandQueue.h"
#include "Dx12_Descriptor.h"
#include "Dx12_ConstantBuffer.h"

#include "Meshes/Dx12_Triangle.h"
#include "Meshes/Dx12_Quad.h"

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
	D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
	cbvDesc.NumDescriptors = 1;
	cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	for (int i = 0; i < gs_frameBufferCount; ++i)
	{
		m_cbv[i] = new Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, cbvDesc, *m_device);
	}
	for (int i = 0; i < gs_frameBufferCount; ++i)
	{
		m_cBuffer[i] = new Dx12_ConstantBuffer(*m_device, *m_cbv[i]);
	}

	m_cmdQueue->ExecuteList(m_cmdList);

	m_cmdQueue->Flush();
}

void Dx12_RenderLayer::MakeTriangle()
{
	m_meshes.push_back(new Dx12_Triangle(MeshType::Triangle, *m_device, m_cmdList));
	m_meshes.push_back(new Dx12_Quad(MeshType::Quad, *m_device, m_cmdList));
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

void Dx12_RenderLayer::Update(float)
{
	m_window->PeekMsg();

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Dx12_RenderLayer::Frame()
{
	
	ID3D12DescriptorHeap* cbvDescriptorHeaps[] = { m_cbv[m_swapChain->GetCurrentFrameIndex()]->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(cbvDescriptorHeaps), cbvDescriptorHeaps);

	m_cmdList->SetPSO(m_currentPso);
	m_cmdList->SetSignature(m_signature);
	m_cmdList->SetViewPort(1);

	//GetCurrentBuffer
	Dx12_ConstantBuffer* cCBuffer = m_cBuffer[m_swapChain->GetCurrentFrameIndex()];

	for (int i = 0; i < m_renderItems.size(); i++)
	{
		int alignmentSize = (cCBuffer->GetBufferAlignment() * i);

		if (m_renderItems[i]->m_shaderId != m_psoCId) {
			m_psoCId = m_renderItems[i]->m_shaderId;
			m_cmdList->SetPSO(m_pipelineStateObjects[m_psoCId]);
		}

		cCBuffer->m_constBufferData.pos.x = m_renderItems[i]->m_position.x;
		cCBuffer->m_constBufferData.pos.y = m_renderItems[i]->m_position.y;
		cCBuffer->CopyData(alignmentSize);

		m_cmdList->Draw(m_renderItems[i], cCBuffer->GetResource(), alignmentSize);
	}

	ID3D12DescriptorHeap* srvDescriptorHeaps[] = { m_srv->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(srvDescriptorHeaps), srvDescriptorHeaps);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_cmdList->GetList());

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_swapChain->GetCurrentBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	m_cmdQueue->ExecuteList(m_cmdList);

	m_swapChain->Present();

	m_renderItems.clear();
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

	m_cmdList->GetList()->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	m_cmdList->GetList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	/*auto dsv = m_dsv->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	m_cmdList->GetList()->ClearDepthStencilView(dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);*/
}

void Dx12_RenderLayer::DestroyLayer()
{
	delete this;
}

void Dx12_RenderLayer::Draw(Drawable a_drawable)
{
	RenderItem* rItem = new RenderItem();
	rItem->m_mesh = m_meshes[(int)a_drawable.meshType];
	rItem->m_shaderId = a_drawable.shaderId;
	rItem->m_typology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	rItem->m_startIndexLocation = 0;
	rItem->m_baseVertexLocation = 0;
	rItem->m_position.x = a_drawable.posX;
	rItem->m_position.y = a_drawable.posY;

	m_renderItems.push_back(rItem);
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
