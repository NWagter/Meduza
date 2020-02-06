#pragma once

#include "../Common/PSO.h"

class Dx12_Device;

enum class ShaderType {
	VertexShader = 0,
	FragmentShader
};

class Dx12_PSO: public PSO{
public:
	Dx12_PSO(int, std::string, std::string, const Dx12_Device&, Microsoft::WRL::ComPtr<ID3D12RootSignature>);


	Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPSO();

private:
	void CreateVertexShader(const wchar_t*);
	void CreatePixelShader(const wchar_t*);

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pso;
	std::unordered_map<ShaderType, Microsoft::WRL::ComPtr<ID3DBlob>> m_shaders;
	std::string m_vertShader;
	std::string m_pixShader;
};