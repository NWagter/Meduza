#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"

#include "Platform/Windows/WinWindow.h"
#include "Platform/Windows/Gfx/Dx12/ContextDx12.h"

#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandQueueDx12.h"
#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"

meduza::renderer::RendererDx12::RendererDx12()
{
	m_context = dynamic_cast<ContextDx12*>(m_window->GetContext());

	m_cmdList = new CommandListDx12(m_context->GetQueue()->GetDesc().Type, *m_context->GetDevice(), m_window->GetSize());

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 3;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new DescriptorDx12(desc, *m_context->GetDevice());
	m_context->CreateRTV(*m_rtv);

	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new DescriptorDx12(srvDesc, *m_context->GetDevice());

#if OPTICK
	ID3D12CommandQueue* cmdQueues[] = { m_context->GetQueue()->GetQueue() };
	OPTICK_GPU_INIT_D3D12(m_context->GetDevice()->GetDevice(), cmdQueues, 1);
#endif

	m_context->GetQueue()->ExecuteList(m_cmdList);
	m_context->GetQueue()->Flush();

}

meduza::renderer::RendererDx12::~RendererDx12()
{
	m_context->GetQueue()->Flush();

	delete m_cmdList;
	delete m_rtv;
	delete m_srv;

	delete m_window;
}

void meduza::renderer::RendererDx12::Clear(Colour a_colour)
{
#if OPTICK
	OPTICK_GPU_EVENT("Clear");
#endif

	auto commandAllocator = m_cmdList->GetCurrentAllocator(m_context->GetCurrentFrameIndex());
	auto backBuffer = m_context->GetCurrentBuffer();

	commandAllocator->Reset();
	m_cmdList->Reset(m_context->GetCurrentFrameIndex());

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_cmdList->GetList()->ResourceBarrier(1, &barrier);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_context->GetCurrentFrameIndex(), m_rtv->GetSize());


	m_cmdList->GetList()->ClearRenderTargetView(rtvHandle, a_colour.m_colour, 0, nullptr);

	m_cmdList->GetList()->OMSetRenderTargets(1, &rtvHandle, 1, nullptr);

}

void meduza::renderer::RendererDx12::SwapBuffers()
{
	PopulateBuffers();

	Renderer::GetWindow().SwapBuffers();
}

void meduza::renderer::RendererDx12::Draw(drawable::Drawable*)
{

}

void meduza::renderer::RendererDx12::Submit(std::vector<drawable::Drawable*>)
{

}

void meduza::renderer::RendererDx12::PreRender()
{
}

void meduza::renderer::RendererDx12::PopulateBuffers()
{
	PreRender();
#if OPTICK
	OPTICK_GPU_EVENT("Render Frame");
#endif // 


	m_cmdList->SetViewPort(1);
	ID3D12DescriptorHeap* srvHeap[] = { m_srv->GetHeap().Get() };
	m_cmdList->GetList()->SetDescriptorHeaps(_countof(srvHeap), srvHeap);
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_context->GetCurrentBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_cmdList->GetList()->ResourceBarrier(1, &barrier);
	m_context->GetQueue()->ExecuteList(m_cmdList);
}
