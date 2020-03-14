#include "cepch.h"
#include "Platform/Windows/DX12_RenderLayer.h"

#include "Gfx/Camera.h"

#include "Platform/Windows/WinWindow.h"
#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_SwapChain.h"
#include "Platform/Windows/DX12_CommandList.h"
#include "Platform/Windows/DX12_CommandQueue.h"
#include "Platform/Windows/DX12_Descriptor.h"
#include "Platform/Windows/DX12_UploadBuffer.h"

#include "Platform/Windows/DX12_RootSignature.h"
#include "Platform/Windows/DX12_PSO.h"

#include "Platform/Windows/DX12_Mesh.h"

#include "Platform/Windows/DX12_Helper.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>
#include <DirectXMathMatrix.inl>
#include "Gfx/IDrawable.h"

cr::DX12_RenderLayer::DX12_RenderLayer(Window & a_window)
{

#if defined(_DEBUG)
	// Always enable the debug layer before doing anything DX12 related
	// so all possible errors generated while creating DX12 objects
	// are caught by the debug layer.
	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
	debugInterface->EnableDebugLayer();

#endif

	m_window = &static_cast<WinWindow&>(a_window);

	//Create the required types
	m_device = new DX12_Device();

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	m_cmdQueue = new DX12_CommandQueue(queueDesc, *m_device);
	m_swapChain = new DX12_SwapChain(*m_device, *m_window, *m_cmdQueue);
	m_cmdList = new DX12_CommandList(queueDesc.Type, *m_device, static_cast<int>(m_window->GetSize().x), static_cast<int>(m_window->GetSize().y));

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 3;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, desc, *m_device);
	m_swapChain->CreateRTV(*m_device, *m_rtv);

	//SRVHeap(Discriptor)
	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, srvDesc, *m_device);

	//RootSignature
	m_rSignature = new DX12_RootSignature(*m_device);

	//PSO

	m_pso = new DX12_PSO("data/shaders/VertexShader.hlsl", "data/shaders/PixelShader.hlsl", *m_device, m_rSignature);


	GeneratePrimitives();

	D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
	cbvDesc.NumDescriptors = 1;
	cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	for (auto& i : m_cbv)
	{
		i = new DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, cbvDesc, *m_device);
	}
	for (int i = 0; i < gs_numBuffers; ++i)
	{
		m_cBuffer[i] = new DX12_UploadBuffer<ConstantBuffer>(*m_device, true);
		m_instanceBuffer[i] = new DX12_UploadBuffer<InstanceBuffer>(*m_device, false);

	}


	InitImGui();

	m_cmdQueue->ExecuteList(m_cmdList);

	m_cmdQueue->Flush();
}

cr::DX12_RenderLayer::~DX12_RenderLayer()
{
	m_cmdQueue->Flush();
	// ImGui shutdown.
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//Clear all data
	delete m_device;
	delete m_swapChain;
	delete m_cmdQueue;
	delete m_cmdList;
	delete m_rtv;
	delete m_srv;
	delete m_pso;
	delete m_rSignature;
	
	for (int i = 0; i < gs_numBuffers; i++)
	{
		delete m_cBuffer[i];
		delete m_cbv[i];
		delete m_instanceBuffer[i];
	}

	for (auto m : m_meshes)
	{
		delete m;
	}

	ClearRenderItems();
}

void cr::DX12_RenderLayer::Clear(float a_colour[4])
{

	if (m_window->GetResize())
	{
		Resize();
		m_window->Resize();
	}

	m_cColour = a_colour;
	//Clear the FrameBuffer
	auto commandAllocator = m_cmdList->GetCurrentAllocator(m_swapChain->GetCurrentFrameIndex());
	auto backBuffer = m_swapChain->GetCurrentBuffer();

	commandAllocator->Reset();
	m_cmdList->Reset(m_swapChain->GetCurrentFrameIndex(), m_pso);

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_swapChain->GetCurrentFrameIndex(), m_rtv->GetSize());

	m_cmdList->GetList()->OMSetRenderTargets(1, &rtvHandle, 0, nullptr);

	m_cmdList->GetList()->ClearRenderTargetView(rtvHandle, m_cColour, 0, nullptr);
}

void cr::DX12_RenderLayer::Render()
{
	//Present the current FrameBuffer
	ID3D12DescriptorHeap* cbvDescriptorHeaps[] = { m_cbv[m_swapChain->GetCurrentFrameIndex()]->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(cbvDescriptorHeaps), cbvDescriptorHeaps);

	m_cmdList->SetPSO(m_pso);
	m_cmdList->SetSignature(m_rSignature);
	m_cmdList->SetViewPort(1);

	auto instanceBuffer = m_instanceBuffer[m_swapChain->GetCurrentFrameIndex()];
	auto cCBuffer = m_cBuffer[m_swapChain->GetCurrentFrameIndex()];

	m_cmdList->GetList()->SetGraphicsRootConstantBufferView(1, cCBuffer->GetResource().Get()->GetGPUVirtualAddress());
	for (int i = 0; i < m_renderables.size(); i++)
	{
		m_cmdList->Draw(m_renderables[i], instanceBuffer->GetResource().Get());
	}


	ID3D12DescriptorHeap* descriptorHeaps[] = { m_srv->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	// Render ImGui
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_cmdList->GetList());


	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_swapChain->GetCurrentBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	m_cmdQueue->ExecuteList(m_cmdList);

	m_swapChain->Present();

	ClearRenderItems();
}

void cr::DX12_RenderLayer::Draw(IDrawable* a_drawable)
{
	auto dData = a_drawable->m_drawData;
	RenderItem* rItem = nullptr;

	if (m_renderables.size() == 0)
	{
		ConstantBuffer data = ConstantBuffer();
		DirectX::XMStoreFloat4x4(&data.m_viewProjectionMat, DirectX::XMMatrixTranspose(DX12_Helper::GlmMat4ToDxMat4(dData.m_viewProjection)));
		auto cBuffer = m_cBuffer[m_swapChain->GetCurrentFrameIndex()];
		cBuffer->CopyData(0, data);
	}

	for (auto rI : m_renderables) {
		if (rI->m_drawType == dData.m_drawtype) 
		{
			rItem = rI;
			break;
		}
	}

	if (rItem == nullptr)
	{
		rItem = new RenderItem();

		rItem->m_mesh = m_meshes[(int)dData.m_drawtype];
		rItem->m_drawType = dData.m_drawtype;
		rItem->m_typology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rItem->m_startIndexLocation = 0;
		rItem->m_baseVertexLocation = 0;

		m_renderables.push_back(rItem);
	}

	InstanceBuffer data = InstanceBuffer();

	DirectX::XMStoreFloat4x4(&data.m_modelMat, DirectX::XMMatrixTranspose(DX12_Helper::GlmMat4ToDxMat4(dData.m_model)));
	data.m_colour = DX12_Helper::GlmVec4ToDxFloat4(dData.m_color);

	rItem->m_instances.push_back(data);
}

void cr::DX12_RenderLayer::Update(float)
{
	//Update Buffers and clear data when possible
	for (int i = 0; i < gs_numBuffers; i++)
	{
		m_instanceBuffer[i]->SetElementCount(*m_device, m_instanceItems, false);
	}

	if (m_window == nullptr)
	{
		delete this; // if there is no window we should delete ourself as we can't exist without a window to draw to
		return;
	}

	auto instanceBuffer = m_instanceBuffer[m_swapChain->GetCurrentFrameIndex()];

	for (auto rI : m_renderables)
	{
		for (int i = 0; i < rI->m_instances.size(); i++)
		{
			if (i >= instanceBuffer->GetElementCount())
			{
				break;
			}

			InstanceBuffer instanceData = InstanceBuffer();

			instanceData.m_modelMat = rI->m_instances[i].m_modelMat;
			instanceData.m_colour = rI->m_instances[i].m_colour;

			int alignmentSize = (instanceBuffer->GetBufferAlignment() * i);
			instanceBuffer->CopyData(alignmentSize, instanceData);
		}

		rI->m_instanceCount = static_cast<int>(rI->m_instances.size());
	}

	// New ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Crime Engine Menu");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::CollapsingHeader("Editor Style"))
	{
		if (ImGui::Button("Classic"))
		{
			ImGui::StyleColorsClassic();
		}
		ImGui::SameLine();

		if (ImGui::Button("Dark"))
		{
			ImGui::StyleColorsDark();
		}
		ImGui::SameLine();

		if (ImGui::Button("Light"))
		{
			ImGui::StyleColorsLight();
		}
	}
	ImGui::End();
}

void cr::DX12_RenderLayer::InitImGui()
{
	// Init ImGui
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	m_imGuiContext = ImGui::CreateContext();
	m_imGuiIO = &ImGui::GetIO();

	// Enable Docking
	m_imGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Set font
	m_imGuiIO->Fonts->AddFontDefault();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(m_window->GetHWND());
	ImGui_ImplDX12_Init(
		m_device->GetDevice(),
		3,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		m_srv->GetHeap().Get(),
		m_srv->GetHeap().Get()->GetCPUDescriptorHandleForHeapStart(),
		m_srv->GetHeap().Get()->GetGPUDescriptorHandleForHeapStart()
	);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

void cr::DX12_RenderLayer::Resize()
{
	RECT rect;
	::GetClientRect(m_window->GetHWND(), &rect);
	int w = static_cast<int>(rect.right - rect.left);
	int h = static_cast<int>(rect.bottom - rect.top);
	ImGui_ImplDX12_InvalidateDeviceObjects();
	m_swapChain->ClearRTV();
	for (auto & i : m_cBuffer)
	{
		i->GetResource().Reset();
	}
	m_swapChain->Resize(w,h);
	m_cmdList->SetViewAndScissor(w, h);
	m_swapChain->CreateRTV(*m_device, *m_rtv);
	ImGui_ImplDX12_CreateDeviceObjects();
}

void cr::DX12_RenderLayer::GeneratePrimitives()
{
	// Traingle
	MeshBuffer mesh;
	mesh.m_vertices = {
		Vertex(0.0f, 0.5f, 0.0f),
		Vertex(0.5f, -0.5f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.0f)
	};
	mesh.m_indices = {
		0, 1, 3
	};

	m_meshes.push_back(new DX12_Mesh(mesh, *m_device, m_cmdList));

	// QUAD
	mesh.m_vertices = {
		Vertex(-0.5f,  0.5f, 0.0f), // top left
		Vertex(0.5f, -0.5f, 0.0f), // bottom right
		Vertex(-0.5f, -0.5f, 0.0f), // bottom left  
		Vertex(0.5f,  0.5f, 0.0f),  // top right
	};
	mesh.m_indices = {
		0, 1, 2,
		0, 3, 1
	};

	m_meshes.push_back(new DX12_Mesh(mesh, *m_device, m_cmdList));
}

void cr::DX12_RenderLayer::ClearRenderItems()
{
	int instanceItems = 0;
	for (auto& renderable : m_renderables)
	{
		instanceItems += static_cast<int>(renderable->m_instances.size());
		delete renderable;
	}

	m_instanceItems = instanceItems;
	m_renderables.clear();
}
