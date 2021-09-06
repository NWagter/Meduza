#pragma once
#include "Platform/General/Resources/MeshBase.h"

namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {
            class Device;
            class CommandList;
        }
    }
    

    namespace Resources
    {
        namespace Dx12
        {
            class Mesh : public MeshBase
            {
            public:
                Mesh(std::string, std::vector<Vertex>, std::vector<uint16_t>, Renderer::Dx12::Device&, Renderer::Dx12::CommandList&);
                virtual ~Mesh();    

                void GenerateBuffers(Renderer::Dx12::Device&, Renderer::Dx12::CommandList&);
                void DisposeUploaders();

                Microsoft::WRL::ComPtr<ID3DBlob> m_vertexBufferCPU = nullptr;
                Microsoft::WRL::ComPtr<ID3DBlob> m_indexBufferCPU = nullptr;

                Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBufferGPU = nullptr;
                Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBufferGPU = nullptr;

                Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBufferUploader = nullptr;
                Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBufferUploader = nullptr;

                D3D12_VERTEX_BUFFER_VIEW GetVertexBuffer() const { return m_vBufferView; };
                D3D12_INDEX_BUFFER_VIEW GetIndexBuffer() const { return m_iBufferView; };

            private:
                DXGI_FORMAT m_indexFormat = DXGI_FORMAT_R32_UINT;

                D3D12_VERTEX_BUFFER_VIEW m_vBufferView;
                D3D12_INDEX_BUFFER_VIEW m_iBufferView;
            };
        }
    }
}