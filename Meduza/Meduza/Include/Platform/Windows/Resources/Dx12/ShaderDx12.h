#pragma once

#include "Platform/General/Resources/Shader.h"

namespace meduza
{
	enum class ShaderType {
		VertexShader = 0,
		FragmentShader
	};

	class ShaderDx12 : public Shader
	{
	public:
		ShaderDx12(unsigned int, std::string);
		ShaderDx12(unsigned int, std::string, std::string);
		void LoadShader();
		~ShaderDx12() override;

		void Reload() override;

		void Bind() override;
		void UnBind() override;

		static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

		inline Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO() { return m_pso; }
		inline Microsoft::WRL::ComPtr<ID3D12RootSignature> GetSignature() { return m_signature; }
	private:

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
