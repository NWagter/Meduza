#pragma once

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/Descriptor.h"

namespace Me
{
    namespace Helper
    {
        namespace Dx12
        {
            struct CameraBuffer
            {
                DirectX::XMFLOAT4X4 m_viewProjection;
            };

            template<typename T>
            class UploadBuffer
            {
            public:
                UploadBuffer(Renderer::Dx12::Device& a_device, bool a_constant)
                {                    
                    CreateResource(a_device, 0, a_constant, true);
                }
                ~UploadBuffer()
                {
                    m_buffer->Release();
                    delete m_data;
                }
                void CopyData(int a_alignment, const T& a_data)
                {
                    memcpy(&m_data[a_alignment], &a_data, sizeof(T));
                }
                void SetElementCount(Renderer::Dx12::Device& a_device, int a_amount, bool a_constant)
                {
                    CreateResource(a_device, a_amount, a_constant);
                }

                inline uint8_t* GetBufferGPUAdress() { return m_gpuAddress; }
                inline Microsoft::WRL::ComPtr<ID3D12Resource> GetResource() { return m_buffer; }
                inline int GetBufferAlignment() { return m_constBufferAlignment; }
                
                inline int GetElementCount() { return m_elementCount; }
            private:
                Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;
                BYTE* m_data;

                uint8_t m_gpuAddress;
                int m_elementCount = 256;
                int m_constBufferAlignment;

                void CreateResource(Renderer::Dx12::Device& a_device, int a_amount, bool a_constant, bool a_onCreate = false)
                {
                    unsigned int byteSize = sizeof(T);

                    if(a_constant)
                    {
                        byteSize = (sizeof(T) + 255) % ~255;
                    }

                    m_constBufferAlignment = byteSize;
                    
                    if(!a_onCreate)
                    {
                        m_buffer.Reset();

                        int size = 256;
                        if (a_amount > 256)
                        {
                            size = a_amount;
                        }

                        m_elementCount = size;
                    }

                    CD3DX12_HEAP_PROPERTIES properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
                    CD3DX12_RESOURCE_DESC resource = CD3DX12_RESOURCE_DESC::Buffer(m_constBufferAlignment * m_elementCount);

                    a_device.GetDevice()->CreateCommittedResource(
                        &properties,
                        D3D12_HEAP_FLAG_NONE,
                        &resource,
                        D3D12_RESOURCE_STATE_GENERIC_READ,
                        nullptr,
                        IID_PPV_ARGS(&m_buffer));

                    m_buffer->SetName(L"Upload Buffer, Resource heap!");

                    m_buffer->Map(0, nullptr, reinterpret_cast<void**>(&m_data));                    
                }
            };
        }
    }
}