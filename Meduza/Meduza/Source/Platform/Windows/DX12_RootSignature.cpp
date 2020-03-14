#include "cepch.h"
#include "Platform/Windows/DX12_RootSignature.h"

#include "Platform/Windows/DX12_Device.h"

cr::DX12_RootSignature::DX12_RootSignature(DX12_Device & a_device)
{

	CD3DX12_ROOT_PARAMETER  rootParameters[2];
	rootParameters[0].InitAsShaderResourceView(0, 1);
	rootParameters[1].InitAsConstantBufferView(0);

	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(_countof(rootParameters),
		rootParameters,
		0,
		nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS);

	ID3DBlob* signature;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr);

	a_device.GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_signature));
}

cr::DX12_RootSignature::~DX12_RootSignature()
{
	m_signature.ReleaseAndGetAddressOf();
}
