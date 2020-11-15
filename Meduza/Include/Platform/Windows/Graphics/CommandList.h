#pragma once
namespace Me 
{
    namespace Resources
    {
        namespace Dx12
        {
            class Mesh;
            class Shader;
        }
    }

    namespace Renderer
    {
        namespace Dx12
        {
            class Device;

            class CommandList
            {
            public:
                CommandList(D3D12_COMMAND_LIST_TYPE, Device*, float, float);
                ~CommandList();

                void Close();
                void Reset(unsigned int, Resources::Dx12::Shader* = nullptr);
                
                inline ID3D12GraphicsCommandList* GetList() { return m_cmdList.Get(); }
                void SetViewPort(int);
                void SetViewAndScissor(float, float);
                Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCurrentAllocator(unsigned int);

                void Draw(Resources::Dx12::Mesh*);
                void Draw(Resources::Dx12::Mesh*, ID3D12Resource*, int);

                bool m_closedList = false;
            private:
                Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateAlloc(D3D12_COMMAND_LIST_TYPE, Device*);
                Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList;
                Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator[3];

                D3D12_RECT m_scissorRect;
                D3D12_VIEWPORT m_viewport;
            };
        }
    }
}