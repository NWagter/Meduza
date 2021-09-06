#pragma once

#include "Platform/General/Resources/ShaderBase.h"

namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {
            class RenderLayerDx12;
        }
    }
    

    namespace Resources
    {
        namespace Dx12
        {
            class Shader : public ShaderBase
            {
            public:
                Shader(std::string, Renderer::Dx12::RenderLayerDx12&);
                void LoadShader();

                virtual ~Shader();   

                void Reload() override;
                void Unload() override;

                void Bind() override;
                void UnBind() override;

                static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

                inline Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO() { return m_pso; }
                inline Microsoft::WRL::ComPtr<ID3D12RootSignature> GetSignature() { return m_signature; }

            private:
                Renderer::Dx12::RenderLayerDx12* m_renderLayer;
                void CreateVertexShader(const wchar_t*);
                void CreatePixelShader(const wchar_t*);
                void CreateSignature();
                void CreatePSO();


                Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pso;
                Microsoft::WRL::ComPtr<ID3D12RootSignature> m_signature;

                std::unordered_map<ShaderType, Microsoft::WRL::ComPtr<ID3DBlob>> m_shaders;

                std::string m_vertShader;
                std::string m_pixShader;
            };
        }
    }
}