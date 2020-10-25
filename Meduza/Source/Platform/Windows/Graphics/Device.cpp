#include "MePCH.h"
#include "Platform/Windows/Graphics/Device.h"

Me::Renderer::Dx12::Device::Device()
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

Me::Renderer::Dx12::Device::~Device()
{
	m_device.ReleaseAndGetAddressOf();
	m_factory.ReleaseAndGetAddressOf();
}