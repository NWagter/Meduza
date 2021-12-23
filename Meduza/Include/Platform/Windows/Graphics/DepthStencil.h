#pragma once

namespace Me
{
    namespace Renderer
    {

        namespace Dx12
        {
            class Device;
            class CommandList;
            class Descriptor;
            
            class DepthStencilBuffer
            {
            public:
                DepthStencilBuffer(Device& a_device, CommandList& a_cmd, int const a_width, int const a_height);
                ~DepthStencilBuffer();

                void SetBuffer(Device& a_device, CommandList& a_cmd, int const a_width, int const a_height);
                D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
            private:
                Microsoft::WRL::ComPtr<ID3D12Resource> m_dsBuffer;
                DXGI_FORMAT m_dsFormat = DXGI_FORMAT_D32_FLOAT;
                Descriptor* m_dsv;
            };
        }
    }
}