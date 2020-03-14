#pragma once


namespace cr {

	class DX12_Device;

	class DX12_RootSignature {
	public:
		DX12_RootSignature(DX12_Device&);
		~DX12_RootSignature();

		const inline Microsoft::WRL::ComPtr<ID3D12RootSignature> GetSiganture() { return m_signature; }

	private:

		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_signature;
	};
}