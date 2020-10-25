#include "MePCH.h"
#include "Platform/Windows/Graphics/Descriptor.h"

#include "Platform/Windows/Graphics/Device.h"

Me::Renderer::Dx12::Descriptor::Descriptor(D3D12_DESCRIPTOR_HEAP_DESC a_desc, Device& a_device)
{
	auto device = &a_device;
	device->GetDevice()->CreateDescriptorHeap(&a_desc, IID_PPV_ARGS(m_heap.GetAddressOf()));
	m_heapSize = device->GetDevice()->GetDescriptorHandleIncrementSize(a_desc.Type);
}

Me::Renderer::Dx12::Descriptor::~Descriptor()
{
	m_heap.ReleaseAndGetAddressOf();
}