#pragma once

class Dx12_Device;

class Dx12_Descriptor {

public:
	Dx12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE, D3D12_DESCRIPTOR_HEAP_DESC, const Dx12_Device&);
	
	const unsigned int GetSize();
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetHeap();
private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_heap;
	unsigned int m_heapSize;
};