#include "cepch.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_Descriptor.h"

cr::DX12_Descriptor::DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE a_type, D3D12_DESCRIPTOR_HEAP_DESC a_desc, DX12_Device& a_device)
{
	a_device.GetDevice()->CreateDescriptorHeap(&a_desc, IID_PPV_ARGS(m_heap.GetAddressOf()));
	m_heapSize = a_device.GetDevice()->GetDescriptorHandleIncrementSize(a_type);
}

cr::DX12_Descriptor::~DX12_Descriptor()
{
	m_heap.ReleaseAndGetAddressOf();
}
