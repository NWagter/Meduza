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
                Fence(Device*);
                ~Fence();

                void WaitForFence(UINT);

                void Flush(CommandQueue&);


                Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
            private:

                unsigned int m_currentFence = 0;
            };
        }
    }
}