#include "pch/pch.h"
#include "Dx12_CommandList.h"

#include "Dx12_Device.h"
#include "Dx12_PSO.h"
#include "Dx12_Mesh.h"

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

	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* signature;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr);
	a_device.m_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_signature));

	m_pso = new Dx12_PSO(0, "Resources\\VertexShader.hlsl", "Resources\\PixelShader.hlsl", a_device, m_signature);

	SetViewAndScissor(a_w, a_h);
}
void Dx12_CommandList::Reset()
{
	GetList()->Reset(m_cmdAllocator->Get(), m_pso->GetPSO().Get());
}
void Dx12_CommandList::Close()
{
	m_commandList->Close();
}

void Dx12_CommandList::Draw(RenderItem* a_rItem)
{
	D3D12_VERTEX_BUFFER_VIEW vBufferView = a_rItem->m_mesh->VertexBufferView();
	m_commandList->IASetVertexBuffers(0, 1, &vBufferView);
	m_commandList->IASetPrimitiveTopology(a_rItem->m_typology);
	m_commandList->DrawInstanced(3, 1, 0, 0);
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Dx12_CommandList::GetCurrentAllocator(int a_id)
{
	return m_cmdAllocator[a_id];
}

ID3D12GraphicsCommandList* Dx12_CommandList::GetList()
{
	return m_commandList.Get();
}

void Dx12_CommandList::SetSignature()
{
	m_commandList->SetGraphicsRootSignature(m_signature.Get());
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
