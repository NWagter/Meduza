#include "cepch.h"
#include "Platform/Windows/DX12_PSO.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_RootSignature.h"

cr::DX12_PSO::DX12_PSO(std::string a_vShader, std::string a_pShader, DX12_Device& a_device, DX12_RootSignature* a_signature)
{
	m_vertShader = a_vShader;
	m_pixShader = a_pShader;

	std::wstring vShaderLoc = std::wstring(a_vShader.begin(), a_vShader.end());
	std::wstring pShaderLoc = std::wstring(a_pShader.begin(), a_pShader.end());

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
	psoDesc.pRootSignature = a_signature->GetSiganture().Get();
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
	blendDesc.AlphaToCoverageEnable = static_cast<int>(true);

	psoDesc.BlendState = blendDesc;
	psoDesc.NumRenderTargets = 1;

	a_device.GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pso));
}

cr::DX12_PSO::~DX12_PSO()
{
	m_pso.ReleaseAndGetAddressOf();
	for (auto s : m_shaders)
	{
		s.second.ReleaseAndGetAddressOf();
	}
}

void cr::DX12_PSO::CreateVertexShader(const wchar_t* a_adress)
{
	D3D12_SHADER_BYTECODE vs = {};

	ID3DBlob* vertexShader;
	ID3DBlob* errorBuff;
	D3DCompileFromFile(a_adress,
		nullptr,
		nullptr,
		"main",
		"vs_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShader,
		&errorBuff);

	vs.BytecodeLength = vertexShader->GetBufferSize();
	vs.pShaderBytecode = vertexShader->GetBufferPointer();

	m_shaders[ShaderType::VertexShader] = vertexShader;
}

void cr::DX12_PSO::CreatePixelShader(const wchar_t* a_adress)
{
	D3D12_SHADER_BYTECODE ps = {};

	ID3DBlob* pixelShader;
	ID3DBlob* errorBuff;
	D3DCompileFromFile(a_adress,
		nullptr,
		nullptr,
		"main",
		"ps_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelShader,
		&errorBuff);

	ps.BytecodeLength = pixelShader->GetBufferSize();
	ps.BytecodeLength = pixelShader->GetBufferSize();
	ps.pShaderBytecode = pixelShader->GetBufferPointer();

	m_shaders[ShaderType::FragmentShader] = pixelShader;
}
