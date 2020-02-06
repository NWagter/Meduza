#include "pch/pch.h"
#include "Dx12_PSO.h"

#include "Dx12_Device.h"

Dx12_PSO::Dx12_PSO(int a_id, std::string a_vertShader, std::string a_pixShader, const Dx12_Device& a_device, Microsoft::WRL::ComPtr<ID3D12RootSignature> a_signature) : PSO(a_id)
{
	m_vertShader = a_vertShader;
	m_pixShader = a_pixShader;

	std::wstring vShaderLoc = std::wstring(a_vertShader.begin(), a_vertShader.end());
	std::wstring pShaderLoc = std::wstring(a_pixShader.begin(), a_pixShader.end());

	CreateVertexShader(vShaderLoc.c_str());
	CreatePixelShader(pShaderLoc.c_str());

	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};

	inputLayoutDesc.NumElements = sizeof(inputLayout) / sizeof(D3D12_INPUT_ELEMENT_DESC);
	inputLayoutDesc.pInputElementDescs = inputLayout;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = inputLayoutDesc;
	psoDesc.pRootSignature = a_signature.Get();
	psoDesc.VS = {
		reinterpret_cast<BYTE*>(m_shaders[ShaderType::VertexShader]->GetBufferPointer()),
		m_shaders[ShaderType::VertexShader]->GetBufferSize()
	};
	psoDesc.PS = {
		reinterpret_cast<BYTE*>(m_shaders[ShaderType::FragmentShader]->GetBufferPointer()),
		m_shaders[ShaderType::FragmentShader]->GetBufferSize()
	};
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc = { 1, 0 };
	psoDesc.SampleMask = 0xffffffff;
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

	D3D12_BLEND_DESC blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	blendDesc.AlphaToCoverageEnable = true;

	psoDesc.BlendState = blendDesc;
	psoDesc.NumRenderTargets = 1;

	a_device.m_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pso));
}

Microsoft::WRL::ComPtr<ID3D12PipelineState> Dx12_PSO::GetPSO()
{
	return m_pso;
}

void Dx12_PSO::CreateVertexShader(const wchar_t* a_shader)
{
	D3D12_SHADER_BYTECODE vs = {};

	ID3DBlob* vertexShader;
	ID3DBlob* errorBuff;
	D3DCompileFromFile(a_shader,
		nullptr,
		nullptr,
		"main",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShader,
		&errorBuff);

	vs.BytecodeLength = vertexShader->GetBufferSize();
	vs.pShaderBytecode = vertexShader->GetBufferPointer();

	m_shaders[ShaderType::VertexShader] = vertexShader;
}

void Dx12_PSO::CreatePixelShader(const wchar_t* a_shader)
{
	D3D12_SHADER_BYTECODE ps = {};

	ID3DBlob* pixelShader;
	ID3DBlob* errorBuff;
	D3DCompileFromFile(a_shader,
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelShader,
		&errorBuff);

	ps.BytecodeLength = pixelShader->GetBufferSize();
	ps.BytecodeLength = pixelShader->GetBufferSize();
	ps.pShaderBytecode = pixelShader->GetBufferPointer();

	m_shaders[ShaderType::FragmentShader] = pixelShader;
}
