#pragma once

namespace mr
{

	class DX12_Device;

	class DX12_Descriptor
	{
	public:
		DX12_Descriptor(D3D12_DESCRIPTOR_HEAP_TYPE, D3D12_DESCRIPTOR_HEAP_DESC, DX12_Device&);
		~DX12_Descriptor();

		inline const unsigned int GetSize() { return m_heapSize; }
		inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetHeap() { return m_heap; }
	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_heap;
		unsigned int m_heapSize;
	};
}
