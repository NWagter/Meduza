#include "mePch.h"

#include "Platform/Windows/Resources/Dx12/ShaderDx12.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"

meduza::ShaderDx12::ShaderDx12(unsigned int a_id, std::string a_path) : Shader(a_id, API::DirectX12)
{
	m_vertShader = a_path;
	m_pixShader = a_path;

	if (renderer::RendererDx12::GetRenderer() != nullptr)
	{
		LoadShader();
	}
}

meduza::ShaderDx12::ShaderDx12(unsigned int a_id, std::string a_vsPath, std::string a_psPath) : Shader(a_id, API::DirectX12)
{
	m_vertShader = a_vsPath;
	m_pixShader = a_psPath;

	if (renderer::RendererDx12::GetRenderer() != nullptr)
	{
		LoadShader();
	}
}

void meduza::ShaderDx12::LoadShader()
{
	std::wstring vShader = std::wstring(m_vertShader.begin(), m_vertShader.end());
	std::wstring pShader = std::wstring(m_pixShader.begin(), m_pixShader.end());

	CreateVertexShader(vShader.c_str());
	CreatePixelShader(pShader.c_str());

	CreateSignature();
	CreatePSO();
}

meduza::ShaderDx12::~ShaderDx12()
{
	m_pso.ReleaseAndGetAddressOf();

	for (auto s : m_shaders)
	{
		s.second.ReleaseAndGetAddressOf();
	}

	m_signature.ReleaseAndGetAddressOf();
}

void meduza::ShaderDx12::Reload()
{
	if (m_pso.Get() != nullptr)
	{
		m_pso.ReleaseAndGetAddressOf();
		for (auto s : m_shaders)
		{
			s.second.ReleaseAndGetAddressOf();
		}
		m_signature.ReleaseAndGetAddressOf();
	}

	LoadShader();
}

void meduza::ShaderDx12::Bind()
{
	auto cmd = renderer::RendererDx12::GetRenderer()->GetCmd();

	cmd.GetList()->SetPipelineState(m_pso.Get());
	cmd.GetList()->SetGraphicsRootSignature(m_signature.Get());
}

void meduza::ShaderDx12::UnBind()
{

}

void meduza::ShaderDx12::CreateVertexShader(const wchar_t* a_path)
{
	D3D12_SHADER_BYTECODE vs = {};

	ID3DBlob* vertexShader;
	ID3DBlob* errorBuff;
	D3DCompileFromFile(a_path,
		nullptr,
		nullptr,
		"VS",
		"vs_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShader,
		&errorBuff);

	vs.BytecodeLength = vertexShader->GetBufferSize();
	vs.pShaderBytecode = vertexShader->GetBufferPointer();

	m_shaders[ShaderType::VertexShader] = vertexShader;
}

void meduza::ShaderDx12::CreatePixelShader(const wchar_t* a_path)
{
	D3D12_SHADER_BYTECODE ps = {};

	ID3DBlob* pixelShader;
	ID3DBlob* errorBuff;
	D3DCompileFromFile(a_path,
		nullptr,
		nullptr,
		"PS",
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

void meduza::ShaderDx12::CreateSignature()
{
	auto device = renderer::RendererDx12::GetRenderer()->GetContext().GetDevice();

	CD3DX12_DESCRIPTOR_RANGE texTable;
	texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0);

	CD3DX12_ROOT_PARAMETER  rootParameters[1];
	//Generate depended on Shader
	rootParameters[0].InitAsConstantBufferView(0);

	auto staticSamplers = GetStaticSamplers();

	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(_countof(rootParameters),
		rootParameters,
		static_cast<unsigned int>(staticSamplers.size()),
		staticSamplers.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* signature;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr);

	device->GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_signature));
}

void meduza::ShaderDx12::CreatePSO()
{
	// Generate Input Layout depending on Shader Layout
	D3D12_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 }
	};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};

	inputLayoutDesc.NumElements = sizeof(layout) / sizeof(D3D12_INPUT_ELEMENT_DESC);
	inputLayoutDesc.pInputElementDescs = layout;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = inputLayoutDesc;
	psoDesc.pRootSignature = m_signature.Get();
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(m_shaders[ShaderType::VertexShader]->GetBufferPointer()),
		m_shaders[ShaderType::VertexShader]->GetBufferSize()
	};
	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(m_shaders[ShaderType::FragmentShader]->GetBufferPointer()),
		m_shaders[ShaderType::FragmentShader]->GetBufferSize()
	};
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	psoDesc.SampleDesc = { 1, 0 };
	psoDesc.SampleMask = 0xffffffff;
	CD3DX12_RASTERIZER_DESC rDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	rDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	psoDesc.RasterizerState = rDesc;

	D3D12_BLEND_DESC blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	blendDesc.AlphaToCoverageEnable = TRUE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	psoDesc.BlendState = blendDesc;
	psoDesc.NumRenderTargets = 1;
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	renderer::RendererDx12::GetRenderer()->GetContext().GetDevice()->GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pso));
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> meduza::ShaderDx12::GetStaticSamplers()
{
	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	return {
		pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp };
}

