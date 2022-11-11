#pragma once
namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {
            class Device;

            class Descriptor
            {
            public:
                Descriptor(D3D12_DESCRIPTOR_HEAP_DESC const a_desc, Device& a_device);
                ~Descriptor();

                inline unsigned int GetSize() const { return m_heapSize; }
                inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetHeap() { return m_heap; }
            private:
                Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_heap;
                unsigned int m_heapSize;
            };
        }
    }
}