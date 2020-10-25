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
#include "Platform/Windows/Gfx/Dx12/DepthStencilDx12.h"

#include "Renderable/Renderable.h"
#include "Scene/Scene.h"

#include "Platform/Windows/Resources/Dx12/MeshDx12.h"
#include "Platform/General/Resources/Material.h"
#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/Windows/Resources/Dx12/ShaderDx12.h"

#include "Camera/Camera.h"

meduza::renderer::RendererDx12* meduza::renderer::RendererDx12::ms_renderer = nullptr;

std::vector<meduza::renderer::UploadBufferDx12<meduza::renderer::ConstBuffer>*> m_cBuffer;

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

	math::Vec2 size = m_context->GetSize();
	m_dsBuffer = new DepthStencilDx12(int(size.m_x), int(size.m_y));

	m_context->GetQueue()->ExecuteList(&GetCmd());
	m_context->GetQueue()->Flush();

	ME_GFX_LOG("DirectX 12 Succesfully loaded!\n");
}

meduza::renderer::RendererDx12::~RendererDx12()
{
	m_renderables.clear();

	for (auto c : m_cBuffer)
	{
		delete c;
	}

	m_cBuffer.clear();

	for (auto c : m_cmdList)
	{
		delete c;
	}

	delete m_rtv;
	delete m_srv;
	delete m_dsBuffer;

	ms_renderer = nullptr;
}

void meduza::renderer::RendererDx12::Clear(Colour a_colour)
{
	for (auto c : m_cBuffer)
	{
		delete c;
	}

	m_cBuffer.clear();
	m_renderables.clear();

	auto cmd = GetCmd();
	auto commandAllocator = cmd.GetCurrentAllocator(m_context->GetCurrentFrameIndex());
	auto backBuffer = m_context->GetCurrentBuffer();

	commandAllocator->Reset();
	cmd.Reset(m_context->GetCurrentFrameIndex(), m_lastShader);
	m_lastShader = nullptr;

	for (auto cL : m_cmdList)
	{
		cL->m_closedList = false;
	}

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmd.GetList()->ResourceBarrier(1, &barrier);
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_context->GetCurrentFrameIndex(), m_rtv->GetSize());

	D3D12_CPU_DESCRIPTOR_HANDLE dvsHandle = m_dsBuffer->DepthStencilView();

	cmd.GetList()->OMSetRenderTargets(1, &rtvHandle, false, &dvsHandle);

	cmd.GetList()->ClearRenderTargetView(rtvHandle, a_colour.m_colour, 0, nullptr);

	cmd.GetList()->ClearDepthStencilView(dvsHandle,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);


}

void meduza::renderer::RendererDx12::Render(const Camera& a_cam)
{
	m_stats.Reset();
	PopulateBuffers(a_cam);
}

void meduza::renderer::RendererDx12::Resize(math::Vec2 a_size)
{
	m_dsBuffer->SetBuffer(int(a_size.m_x), int(a_size.m_y));
	GetCmd().SetViewAndScissor(a_size);
}

void meduza::renderer::RendererDx12::Submit(Renderable& a_renderable)
{
	m_renderables.push_back(&a_renderable);
}

void meduza::renderer::RendererDx12::Submit(Scene& a_scene)
{
	for (auto r : a_scene.GetRenderables())
	{
		Submit(*r);
	}
}

void meduza::renderer::RendererDx12::PreRender()
{

}

void meduza::renderer::RendererDx12::PopulateBuffers(const Camera& a_cam)
{
	glm::mat4 camera = a_cam.GetViewProjection();


	DirectX::XMMATRIX vProjection(
		camera[0][0], camera[0][1], camera[0][2], camera[0][3],
		camera[1][0], camera[1][1], camera[1][2], camera[1][3],
		camera[2][0], camera[2][1], camera[2][2], camera[2][3],
		camera[3][0], camera[3][1], camera[3][2], camera[3][3]
	);

	for (auto r : m_renderables)
	{
		//ViewProjection.
		ConstBuffer cData = ConstBuffer();

		DirectX::XMStoreFloat4x4(&cData.m_viewProjection, DirectX::XMMatrixTranspose(vProjection));

		UploadBufferDx12<ConstBuffer>* cBuffer = new UploadBufferDx12<ConstBuffer>(true);

		auto p = r->GetTransform().Position();
		cData.m_position = DirectX::XMFLOAT3(p.m_xyz);
		auto s = r->GetTransform().GetPixelScale();
		cData.m_scale = DirectX::XMFLOAT3(s.m_xyz);

		cBuffer->CopyData(0, cData);

		m_cBuffer.push_back(cBuffer);
	}

	PreRender();

	ID3D12DescriptorHeap* srvHeap[] = { m_srv->GetHeap().Get() };
	GetCmd().GetList()->SetDescriptorHeaps(_countof(srvHeap), srvHeap);

	GetCmd().SetViewPort(1);

	int i = 0;
	for (auto r : m_renderables)
	{
		m_stats.m_drawables++;
		m_stats.m_vertices += r->GetMesh().GetVerticesSize();
		m_stats.m_drawCalls++;

		if(m_lastShader == nullptr || m_lastShader->GetId() != r->GetMaterial().GetShaderID()) // only change when shader / pso changes
		{
			m_lastShader = static_cast<ShaderDx12*>(ShaderLibrary::GetShader(r->GetMaterial().GetShaderID()));
			m_lastShader->Bind();
		}

		GetCmd().GetList()->SetGraphicsRootConstantBufferView(0, m_cBuffer.at(i)->GetResource().Get()->GetGPUVirtualAddress());

		MeshDx12* m = static_cast<MeshDx12*>(&r->GetMesh());
		GetCmd().Draw(m);
		i++;
	}

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
