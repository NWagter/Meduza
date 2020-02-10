#pragma once

class Dx12_Device;

class Dx12_RootSignature {
public:
	Dx12_RootSignature(const Dx12_Device&);
	~Dx12_RootSignature();

	const Microsoft::WRL::ComPtr<ID3D12RootSignature> GetSiganture();

private:

	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_signature;
};