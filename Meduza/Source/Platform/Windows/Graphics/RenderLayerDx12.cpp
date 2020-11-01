#include "MePCH.h"
#include "Platform/Windows/Graphics/RenderLayerDx12.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/Graphics/Context.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/Graphics/CommandQueue.h"
#include "Platform/Windows/Graphics/Descriptor.h"

#include "Platform/Windows/Resources/Mesh.h"
#include "Platform/General/MeshLibrary.h"
#include "Platform/Windows/Resources/Shader.h"
#include "Platform/General/ShaderLibrary.h"

Me::Renderer::Dx12::RenderLayerDx12::RenderLayerDx12(Me::Window* a_window)
{
    if(a_window == nullptr)
    {
        printf("Window is Null!");
        return;
    }

    //cast the window into a WindowsWindow type
    m_window = dynamic_cast<WindowsWindow*>(a_window);

    m_device = new Device();
    m_context = new Context(m_window->GetWindowHandle(), m_device);
	m_window->SetContext(m_context);

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	m_queue = new CommandQueue(queueDesc, m_device);
    m_context->SetQueue(*m_queue);
    
	m_cmd.push_back(new CommandList(m_context->GetQueue()->GetDesc().Type, m_device, m_context->m_width, m_context->m_height));

    m_context->CreateSwapchain();
    
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 3;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new Descriptor(desc, *m_device);
	m_context->CreateRTV(*m_rtv);


    D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new Descriptor(srvDesc, *m_device);

	m_activeShader = nullptr;
}

Me::Renderer::Dx12::RenderLayerDx12::~RenderLayerDx12()
{
    m_queue->Flush();

    delete m_context;
    delete m_device;
    delete m_queue;
}

void Me::Renderer::Dx12::RenderLayerDx12::Clear(Colour a_colour)
{
	m_renderables.clear();
	auto cmd = GetCmd();
	auto commandAllocator = cmd.GetCurrentAllocator(m_context->GetCurrentFrameIndex());
	auto backBuffer = m_context->GetCurrentBuffer();

    commandAllocator->Reset();
	cmd.Reset(m_context->GetCurrentFrameIndex(), m_activeShader);

    for (auto cL : m_cmd)
	{
		cL->m_closedList = false;
	}

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmd.GetList()->ResourceBarrier(1, &barrier);
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_context->GetCurrentFrameIndex(), m_rtv->GetSize());

	cmd.GetList()->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	cmd.GetList()->ClearRenderTargetView(rtvHandle, a_colour.m_colour, 0, nullptr);
}

void Me::Renderer::Dx12::RenderLayerDx12::Present()
{
	GetCmd().SetViewPort(1);
	Populate();


    m_context->SwapBuffers(GetCmd());
}

void Me::Renderer::Dx12::RenderLayerDx12::Submit(Renderable& a_renderable)
{
    m_renderables.push_back(&a_renderable);
}


void Me::Renderer::Dx12::RenderLayerDx12::Populate()
{
	for (auto r : m_renderables)
	{
		auto s = static_cast<Resources::Dx12::Shader*>(Resources::ShaderLibrary::GetShader(r->m_shader));
		auto m = static_cast<Resources::Dx12::Mesh*>(Resources::MeshLibrary::GetMesh(r->m_mesh));
		if(m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
		{
			m_activeShader = s;
			m_activeShader->Bind();
		}

		GetCmd().Draw(m);
	}
}

Me::Renderer::Dx12::CommandList& Me::Renderer::Dx12::RenderLayerDx12::GetCmd(int a_id)
{
    auto cmd = m_cmd.at(a_id);
	if (cmd == nullptr)
	{
		return *cmd;
	}

	return *cmd;
}

Me::Renderer::Dx12::Device& Me::Renderer::Dx12::RenderLayerDx12::GetDevice()
{
	return *m_device;
}

Me::Resources::Dx12::Mesh* Me::Renderer::Dx12::RenderLayerDx12::CreateMesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
	return new Me::Resources::Dx12::Mesh(a_vertices,a_indices, *m_device, GetCmd());
}