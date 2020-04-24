#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"

meduza::renderer::DescriptorDx12::DescriptorDx12(D3D12_DESCRIPTOR_HEAP_DESC a_desc, DeviceDx12& a_device)
{
	a_device.GetDevice()->CreateDescriptorHeap(&a_desc, IID_PPV_ARGS(m_heap.GetAddressOf()));
	m_heapSize = a_device.GetDevice()->GetDescriptorHandleIncrementSize(a_desc.Type);
}

meduza::renderer::DescriptorDx12::~DescriptorDx12()
{
	m_heap.ReleaseAndGetAddressOf();
}
