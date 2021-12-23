#pragma once
namespace Me 
{
    namespace Renderer
    {
        namespace Dx12
        {
            class Device;
            class CommandQueue;
            
            class Fence
            {
            public:
                Fence(Device* a_device);
                ~Fence();

                void WaitForFence(UINT const a_fValue);

                void Flush(CommandQueue& a_queue);


                Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
            private:

                unsigned int m_currentFence = 0;
            };
        }
    }
}