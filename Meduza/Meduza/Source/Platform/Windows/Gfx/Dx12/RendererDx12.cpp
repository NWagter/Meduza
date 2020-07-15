#include "mePch.h"

#include "Core.h"
#include "Platform/General/Utils/MeduzaHelper.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"

#include "Platform/Windows/Window/WinWindow.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"

#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandQueueDx12.h"
#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"

meduza::renderer::RendererDx12* meduza::renderer::RendererDx12::ms_renderer = nullptr;

meduza::renderer::RendererDx12::RendererDx12(Context& a_context)
{
	if (ms_renderer == nullptr)
	{
		ms_renderer = this;
	}

	m_context = dynamic_cast<ContextDx12*>(&a_context);

	m_cmdList.push_back(new CommandListDx12(m_context->GetQueue()->GetDesc().Type, m_context->GetSize()));

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 3;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new DescriptorDx12(desc);
	m_context->CreateRTV(*m_rtv);

	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new DescriptorDx12(srvDesc);

	m_context->GetQueue()->ExecuteList(&GetCmd());
	m_context->GetQueue()->Flush();

	ME_GFX_LOG("DirectX 12 Succesfully loaded!\n");
}

meduza::renderer::RendererDx12::~RendererDx12()
{	
	for (auto c : m_cmdList)
	{
		delete c;
	}
	delete m_rtv;
	delete m_srv;
	ms_renderer = nullptr;
}

void meduza::renderer::RendererDx12::Clear(Colour a_colour)
{
	auto cmd = GetCmd();
	auto commandAllocator = cmd.GetCurrentAllocator(m_context->GetCurrentFrameIndex());
	auto backBuffer = m_context->GetCurrentBuffer();

	commandAllocator->Reset();
	cmd.Reset(m_context->GetCurrentFrameIndex());

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmd.GetList()->ResourceBarrier(1, &barrier);
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_context->GetCurrentFrameIndex(), m_rtv->GetSize());
	cmd.GetList()->OMSetRenderTargets(1, &rtvHandle, 1, nullptr);

	cmd.GetList()->ClearRenderTargetView(rtvHandle, a_colour.m_colour, 0, nullptr);
}

void meduza::renderer::RendererDx12::Render(const Camera&)
{
	PopulateBuffers();
}

void meduza::renderer::RendererDx12::Submit(Renderable&)
{
}

void meduza::renderer::RendererDx12::Submit(Scene&)
{
}

void meduza::renderer::RendererDx12::PreRender()
{
}

void meduza::renderer::RendererDx12::PopulateBuffers()
{
	PreRender();

	GetCmd().SetViewPort(1);
	ID3D12DescriptorHeap* srvHeap[] = { m_srv->GetHeap().Get() };
	GetCmd().GetList()->SetDescriptorHeaps(_countof(srvHeap), srvHeap);


}

meduza::renderer::ContextDx12& meduza::renderer::RendererDx12::GetContext() const
{
	if (m_context == nullptr)
	{
		ME_GFX_ASSERT_M(0, "No Context Available!");
		return *m_context;
	}
		
	return *m_context; 
}

meduza::renderer::CommandListDx12& meduza::renderer::RendererDx12::GetCmd(int a_id) const
{
	auto cmd = m_cmdList.at(a_id);
	if (cmd == nullptr)
	{
		ME_GFX_ASSERT_M(0, "No Command List Available!");
		return*cmd;
	}

	return *cmd;
}

meduza::renderer::DrawStatistics meduza::renderer::RendererDx12::GetDrawStatistics() const
{
	return m_stats;
}

meduza::renderer::RendererDx12* meduza::renderer::RendererDx12::GetRenderer()
{
	if (ms_renderer == nullptr)
	{
		ME_CORE_ASSERT_M(true, "There is no Renderer!");
		return nullptr;
	}
	return ms_renderer;
}
