#include "mePch.h"

#include "Gfx/DirectX12/DeviceDX12.h"

meduza::renderer::DeviceDX12::DeviceDX12()
{
}

meduza::renderer::DeviceDX12::~DeviceDX12()
{
	m_device.ReleaseAndGetAddressOf();
	m_factory.ReleaseAndGetAddressOf();
}
