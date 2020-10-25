#pragma once
namespace Me 
{
    namespace Renderer
    {
        namespace Dx12
        {
        class Device;
        class CommandList;
        class Fence;

            class CommandQueue
            {
            public:
                CommandQueue(D3D12_COMMAND_QUEUE_DESC, Device*);
                ~CommandQueue();

                inline D3D12_COMMAND_QUEUE_DESC GetDesc() { return m_description; }
                inline ID3D12CommandQueue* GetQueue() { return m_queue.Get(); }
                void ExecuteList(CommandList*);
                void Flush();

            private:

                Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_queue;
                D3D12_COMMAND_QUEUE_DESC m_description;

                Fence* m_fence;
            };
        }
    }
}
