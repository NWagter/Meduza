#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"

#include "Platform/Windows/Resources/Dx12/MeshDx12.h"
#include "Platform/Windows/Resources/Dx12/ShaderDx12.h"

meduza::renderer::CommandListDx12::CommandListDx12(D3D12_COMMAND_LIST_TYPE a_type, math::Vec2 a_size)
{
	auto device = RendererDx12::GetRenderer()->GetContext().GetDevice();
	for (auto& i : m_cmdAllocator)
	{
		i = CreateAlloc(a_type);
	}


	device->GetDevice()->CreateCommandList(
		0,
		a_type,
		m_cmdAllocator->Get(),
		nullptr,
		IID_PPV_ARGS(m_cmdList.GetAddressOf()));

	SetViewAndScissor(a_size);
}

meduza::renderer::CommandListDx12::~CommandListDx12()
{
	m_cmdList.ReleaseAndGetAddressOf();
	m_cmdAllocator->ReleaseAndGetAddressOf();
}

void meduza::renderer::CommandListDx12::Close()
{
	m_closedList = true;
	m_cmdList->Close();
}

void meduza::renderer::CommandListDx12::Reset(unsigned int a_frame, ShaderDx12* a_shader)
{
	if (a_shader == nullptr)
	{
		GetList()->Reset(m_cmdAllocator[a_frame].Get(), nullptr);
	}
	else
	{
		GetList()->Reset(m_cmdAllocator[a_frame].Get(), a_shader->GetPSO().Get());
	}
}

void meduza::renderer::CommandListDx12::SetViewPort(int a_port)
{
	m_cmdList->RSSetViewports(a_port, &m_viewport);
	m_cmdList->RSSetScissorRects(a_port, &m_scissorRect);
}

void meduza::renderer::CommandListDx12::SetViewAndScissor(math::Vec2 a_size)
{
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = a_size.m_x;
	vp.Height = a_size.m_y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_viewport = vp;

	m_scissorRect = { 0,0, int(a_size.m_x), int(a_size.m_y) };
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> meduza::renderer::CommandListDx12::GetCurrentAllocator(unsigned int a_id)
{
	return m_cmdAllocator[a_id];
}

void meduza::renderer::CommandListDx12::Draw(MeshDx12* a_mesh)
{
	if (a_mesh->m_vertexBufferGPU.Get() == nullptr)
	{
		a_mesh->GenerateBuffers();
	}


	D3D12_VERTEX_BUFFER_VIEW vBuffer = a_mesh->GetVertexBuffer();
	m_cmdList->IASetVertexBuffers(0, 1, &vBuffer);
	m_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	D3D12_INDEX_BUFFER_VIEW iBuffer = a_mesh->GetIndexBuffer();
	m_cmdList->IASetIndexBuffer(&iBuffer);

	//m_cmdList->DrawInstanced(a_mesh->GetIndicesSize(), 1, 0, 0);
	m_cmdList->DrawIndexedInstanced(a_mesh->GetIndicesSize(), 1, 0, 0, 0);
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> meduza::renderer::CommandListDx12::CreateAlloc(D3D12_COMMAND_LIST_TYPE a_type)
{
	auto device = RendererDx12::GetRenderer()->GetContext().GetDevice();
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	device->GetDevice()->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator));

	return commandAllocator;
}
