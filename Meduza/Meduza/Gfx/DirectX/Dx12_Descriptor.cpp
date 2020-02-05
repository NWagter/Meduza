#include "pch/pch.h"
#include "Dx12_Descriptor.h"

#include "Dx12_Device.h"

Dx12_Descriptor::Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE a_Type, D3D12_DESCRIPTOR_HEAP_DESC a_Desc, const Dx12_Device& a_device)
{
	ThrowIfFailed(a_device.m_device->CreateDescriptorHeap(&a_Desc, IID_PPV_ARGS(m_heap.GetAddressOf())));
	m_heapSize = a_device.m_device->GetDescriptorHandleIncrementSize(a_Type);
}

const unsigned int Dx12_Descriptor::GetSize()
{
	return m_heapSize;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> Dx12_Descriptor::GetHeap()
{
	return m_heap;
}
