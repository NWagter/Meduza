#include "pch/pch.h"
#include "Dx12_RootSignature.h"

#include "Dx12_Device.h"

Dx12_RootSignature::Dx12_RootSignature(const Dx12_Device& a_device)
{
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* signature;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr);
	a_device.m_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_signature));
}

Dx12_RootSignature::~Dx12_RootSignature()
{
	m_signature.ReleaseAndGetAddressOf();
}

const Microsoft::WRL::ComPtr<ID3D12RootSignature> Dx12_RootSignature::GetSiganture()
{
	return m_signature;
}
