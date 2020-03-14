#pragma once


namespace cr {

	class DX12_RootSignature;
	class DX12_Device;

	enum class ShaderType {
		VertexShader = 0,
		FragmentShader
	};

	class DX12_PSO {
	public:
		DX12_PSO(std::string, std::string, DX12_Device&, DX12_RootSignature*);
		~DX12_PSO();

		inline Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO() { return m_pso; }

	private:
		void CreateVertexShader(const wchar_t*);
		void CreatePixelShader(const wchar_t*);

		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pso;
		std::unordered_map<ShaderType, Microsoft::WRL::ComPtr<ID3DBlob>> m_shaders;
		std::string m_vertShader;
		std::string m_pixShader;
	};
}