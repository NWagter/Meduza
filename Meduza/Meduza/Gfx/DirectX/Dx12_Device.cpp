#include "pch/pch.h"
#include "Dx12_Device.h"

Dx12_Device::~Dx12_Device()
{
	DestroyDevice();
}

void Dx12_Device::InitDevice()
{
	ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&m_factory)));
	HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));

	if (FAILED(hr))
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
		ThrowIfFailed(m_factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device)));
	}
}

void Dx12_Device::DestroyDevice()
{
	m_device.ReleaseAndGetAddressOf();
	m_factory.ReleaseAndGetAddressOf();
}
