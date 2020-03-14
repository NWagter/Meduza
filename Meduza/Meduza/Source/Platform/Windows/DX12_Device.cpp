#include "cepch.h"
#include "Platform/Windows/DX12_Device.h"

cr::DX12_Device::DX12_Device()
{
	
	CreateDXGIFactory(IID_PPV_ARGS(&m_factory));
	HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));

	if (FAILED(hr))
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
		m_factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));

		D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));
	}
}

cr::DX12_Device::~DX12_Device()
{
	m_device.ReleaseAndGetAddressOf();
	m_factory.ReleaseAndGetAddressOf();
}
