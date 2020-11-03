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
                DepthStencilBuffer(Device&, CommandList&, int, int);
                ~DepthStencilBuffer();

                void SetBuffer(Device&, CommandList&, int, int);
                D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
            private:
                Microsoft::WRL::ComPtr<ID3D12Resource> m_dsBuffer;
                DXGI_FORMAT m_dsFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
                Descriptor* m_dsv;
            };
        }
    }
}