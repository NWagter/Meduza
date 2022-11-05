#pragma once
namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {
            class Device
            {
            public:
                Device();
                ~Device();

                inline ID3D12Device2* GetDevice() { return m_device.Get(); }
                inline IDXGIFactory4* GetFactory() { return m_factory.Get(); }

            private:
                Microsoft::WRL::ComPtr<ID3D12Device2> m_device;
                Microsoft::WRL::ComPtr<IDXGIFactory4> m_factory;
            };
        }
    }
}