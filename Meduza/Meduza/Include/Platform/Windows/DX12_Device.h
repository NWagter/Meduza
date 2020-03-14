#pragma once

namespace cr {

	class DX12_Device {

	public:
		DX12_Device();
		~DX12_Device();

		inline ID3D12Device2* GetDevice() { return m_device.Get(); }
		inline IDXGIFactory4* GetFactory() { return m_factory.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D12Device2> m_device;
		Microsoft::WRL::ComPtr<IDXGIFactory4> m_factory;
	};
}