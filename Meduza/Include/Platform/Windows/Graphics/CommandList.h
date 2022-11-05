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
                struct DrawOutput
                {
                    uint16_t m_vertices;
                };

                CommandList(D3D12_COMMAND_LIST_TYPE const a_type, Device* a_device, float const a_width, float const a_height);
                ~CommandList();

                void Close();
                void Reset(unsigned const int a_frame, Resources::Dx12::Shader* a_shader = nullptr);

                inline ID3D12GraphicsCommandList* GetList() const { return m_cmdList.Get(); }
                void SetViewPort(int const a_index);
                void SetViewAndScissor(float const a_width, float const a_height);
                Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCurrentAllocator(unsigned int const a_index);

                void Draw(Resources::Dx12::Mesh* a_mesh, DrawOutput& a_drawOutput);
                void Draw(Resources::Dx12::Mesh* a_mesh, ID3D12Resource* a_heaps, int const a_count, DrawOutput& a_drawOutput);

                bool m_closedList = false;
            private:
                Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateAlloc(D3D12_COMMAND_LIST_TYPE const, Device*);
                Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList;
                Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator[3];

                D3D12_RECT m_scissorRect;
                D3D12_VIEWPORT m_viewport;
            };
        }
    }
}