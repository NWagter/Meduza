#include "cepch.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_CommandList.h"
#include "Platform/Windows/DX12_PSO.h"
#include "Platform/Windows/DX12_RootSignature.h"

#include "Platform/Windows/DX12_Mesh.h"


cr::DX12_CommandList::DX12_CommandList(D3D12_COMMAND_LIST_TYPE a_type, DX12_Device& a_device, int a_w, int a_h)
{
	for (auto & i : m_cmdAllocator)
	{
		i = CreateAlloc(a_device, a_type);
	}


	a_device.GetDevice()->CreateCommandList(
		0,
		a_type,
		m_cmdAllocator->Get(),
		nullptr,
		IID_PPV_ARGS(m_cmdList.GetAddressOf()));

	SetViewAndScissor(a_w, a_h);
}

cr::DX12_CommandList::~DX12_CommandList()
{	
	m_cmdList.ReleaseAndGetAddressOf();
	m_cmdAllocator->ReleaseAndGetAddressOf();
}

void cr::DX12_CommandList::Close()
{
	m_cmdList->Close();
}

void cr::DX12_CommandList::Reset(int a_frame, DX12_PSO* a_pso)
{
	GetList()->Reset(m_cmdAllocator[a_frame].Get(), a_pso->GetPSO().Get());
}

void cr::DX12_CommandList::Draw(RenderItem* a_item, ID3D12Resource* a_heaps)
{
	// set the root descriptor table 0 to the constant buffer descriptor heap
	m_cmdList->SetGraphicsRootShaderResourceView(0, a_heaps->GetGPUVirtualAddress());

	D3D12_VERTEX_BUFFER_VIEW vBufferView = a_item->m_mesh->VertexBufferView();
	m_cmdList->IASetVertexBuffers(0, 1, &vBufferView);
	m_cmdList->IASetPrimitiveTopology(a_item->m_typology);

	if (a_item->m_drawType == DrawType::Triangle)
	{
		m_cmdList->DrawInstanced(a_item->m_mesh->GetIndexCount(), 1, 0, 0);
	}
	else {
		D3D12_INDEX_BUFFER_VIEW iBufferView = a_item->m_mesh->IndexBufferView();
		m_cmdList->IASetIndexBuffer(&iBufferView);
		m_cmdList->DrawIndexedInstanced(a_item->m_mesh->GetIndexCount(),
			a_item->m_instanceCount,
			a_item->m_startIndexLocation,
			a_item->m_baseVertexLocation, 1);
	}
}

void cr::DX12_CommandList::SetViewPort(int a_port)
{
	m_cmdList->RSSetViewports(a_port, &m_viewport);
	m_cmdList->RSSetScissorRects(a_port, &m_scissorRect);
}

void cr::DX12_CommandList::SetViewAndScissor(int a_w, int a_h)
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

void cr::DX12_CommandList::SetPSO(DX12_PSO* a_pso)
{
	m_cmdList->SetPipelineState(a_pso->GetPSO().Get());
}

void cr::DX12_CommandList::SetSignature(DX12_RootSignature* a_signature)
{
	m_cmdList->SetGraphicsRootSignature(a_signature->GetSiganture().Get());
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cr::DX12_CommandList::GetCurrentAllocator(int a_id)
{
	return m_cmdAllocator[a_id];
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cr::DX12_CommandList::CreateAlloc(DX12_Device& a_device, D3D12_COMMAND_LIST_TYPE a_type)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	a_device.GetDevice()->CreateCommandAllocator(a_type, IID_PPV_ARGS(&commandAllocator));

	return commandAllocator;
}
