#include "MePCH.h"
#include "Platform/Windows/Graphics/CommandList.h"

#include "Platform/Windows/Graphics/Device.h"

#include "Platform/Windows/Resources/Mesh.h"
#include "Platform/Windows/Resources/Shader.h"

Me::Renderer::Dx12::CommandList::CommandList(D3D12_COMMAND_LIST_TYPE a_type, Device* a_device, float a_x, float a_y)
{
    for (auto& alloc : m_cmdAllocator)
	{
		alloc = CreateAlloc(a_type, a_device);
	}

    a_device->GetDevice()->CreateCommandList(
        0,
        a_type,
        m_cmdAllocator->Get(),
        nullptr,
        IID_PPV_ARGS(m_cmdList.GetAddressOf()));
    
    m_cmdList.Get()->SetName(L"Command List");
    SetViewAndScissor(a_x,a_y);
}

Me::Renderer::Dx12::CommandList::~CommandList()
{
	m_cmdList.ReleaseAndGetAddressOf();

	m_cmdAllocator->ReleaseAndGetAddressOf();
}

void Me::Renderer::Dx12::CommandList::Close()
{
    m_closedList = true;
    m_cmdList->Close();
}

void Me::Renderer::Dx12::CommandList::Reset(unsigned int a_frame, Resources::Dx12::Shader* a_shader)
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


void Me::Renderer::Dx12::CommandList::SetViewPort(int a_port)
{
	m_cmdList->RSSetViewports(a_port, &m_viewport);
	m_cmdList->RSSetScissorRects(a_port, &m_scissorRect);
}

void Me::Renderer::Dx12::CommandList::SetViewAndScissor(float a_x, float a_y)
{
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = a_x;
	vp.Height = a_y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_viewport = vp;

	m_scissorRect = { 0,0, int(a_x), int(a_y) };
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Me::Renderer::Dx12::CommandList::GetCurrentAllocator(unsigned int a_id)
{
	return m_cmdAllocator[a_id];
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Me::Renderer::Dx12::CommandList::CreateAlloc(D3D12_COMMAND_LIST_TYPE a_type, Device* a_device)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	a_device->GetDevice()->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator));

	return commandAllocator;
}

void Me::Renderer::Dx12::CommandList::Draw(Resources::Dx12::Mesh* a_mesh)
{
	D3D12_VERTEX_BUFFER_VIEW vBuffer = a_mesh->GetVertexBuffer();
	m_cmdList->IASetVertexBuffers(0, 1, &vBuffer);
	m_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	D3D12_INDEX_BUFFER_VIEW iBuffer = a_mesh->GetIndexBuffer();
	m_cmdList->IASetIndexBuffer(&iBuffer);

	//m_cmdList->DrawInstanced(a_mesh->GetIndicesSize(), 1, 0, 0);
	m_cmdList->DrawIndexedInstanced(a_mesh->GetIndicesSize(), 1, 0, 0, 0);
}