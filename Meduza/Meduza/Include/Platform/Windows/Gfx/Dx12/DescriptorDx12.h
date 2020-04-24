#pragma once

namespace meduza
{
	namespace renderer
	{
		class DeviceDx12;

		class DescriptorDx12
		{
		public:
			DescriptorDx12(D3D12_DESCRIPTOR_HEAP_DESC, DeviceDx12&);
			~DescriptorDx12();

			inline unsigned int GetSize() const { return m_heapSize; }
			inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetHeap() { return m_heap; }
		private:
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_heap;
			unsigned int m_heapSize;
		};
	}
}