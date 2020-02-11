#include "pch/pch.h"
#include "Dx12_CommandList.h"

#include "Dx12_Device.h"
#include "Dx12_PSO.h"
#include "Meshes\Dx12_Mesh.h"

#include "Dx12_RootSignature.h"

Dx12_CommandList::Dx12_CommandList(D3D12_COMMAND_LIST_TYPE a_type, const Dx12_Device& a_device, int a_w, int a_h)
{
	for (int i = 0; i < gs_frameBufferCount; i++)
	{
		m_cmdAllocator[i] = CreateAlloc(a_device, a_type);
	}


	ThrowIfFailed(a_device.m_device->CreateCommandList(
		0,
		a_type,
		m_cmdAllocator->Get(),
		nullptr,
		IID_PPV_ARGS(m_commandList.GetAddressOf())));

	SetViewAndScissor(a_w, a_h);
}

Dx12_CommandList::~Dx12_CommandList()
{
	m_commandList.ReleaseAndGetAddressOf();
	for (int i = 0; i < gs_frameBufferCount; i++)
	{
		m_cmdAllocator[i].ReleaseAndGetAddressOf();
	}
}

void Dx12_CommandList::Reset(int a_frameId, PSO* a_pso)
{
	Dx12_PSO* pso = static_cast<Dx12_PSO*>(a_pso);
	GetList()->Reset(m_cmdAllocator[a_frameId].Get(), pso->GetPSO().Get());
}
void Dx12_CommandList::Close()
{
	m_commandList->Close();
}

void Dx12_CommandList::Draw(RenderItem* a_rItem)
{
	D3D12_VERTEX_BUFFER_VIEW vBufferView = a_rItem->m_mesh->VertexBufferView();

	D3D12_INDEX_BUFFER_VIEW iBufferView = a_rItem->m_mesh->IndexBufferView();

	m_commandList->IASetVertexBuffers(0, 1, &vBufferView);

	m_commandList->IASetIndexBuffer(&iBufferView);

	m_commandList->IASetPrimitiveTopology(a_rItem->m_typology);
	//m_commandList->DrawInstanced(a_rItem->m_indexCount, 1, 0, 0);

	m_commandList->DrawIndexedInstanced(a_rItem->m_indexCount, 1, a_rItem->m_startIndexLocation, a_rItem->m_baseVertexLocation, 0);
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Dx12_CommandList::GetCurrentAllocator(int a_id)
{
	return m_cmdAllocator[a_id];
}

ID3D12GraphicsCommandList* Dx12_CommandList::GetList()
{
	return m_commandList.Get();
}

void Dx12_CommandList::SetPSO(Dx12_PSO* a_pso)
{
	m_commandList->SetPipelineState(a_pso->GetPSO().Get());
}

void Dx12_CommandList::SetSignature(Dx12_RootSignature* a_signature)
{
	m_commandList->SetGraphicsRootSignature(a_signature->GetSiganture().Get());
}

void Dx12_CommandList::SetViewPort(int a_numViewport)
{
	m_commandList->RSSetViewports(a_numViewport, &m_viewport);
	m_commandList->RSSetScissorRects(a_numViewport, &m_scissorRect);
}

void Dx12_CommandList::SetViewAndScissor(int a_w, int a_h)
{
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(a_w);
	vp.Height = static_cast<float>(a_h);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_viewport = vp;

	m_scissorRect = { 0,0, a_w, a_h };
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Dx12_CommandList::CreateAlloc(const Dx12_Device& a_device, D3D12_COMMAND_LIST_TYPE a_type)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	ThrowIfFailed(a_device.m_device->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator)));

	return commandAllocator;
}
