#include "MePCH.h"
#include "Platform/Windows/Resources/Shader.h"

#include "Platform/Windows/Graphics/RenderLayerDx12.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"

Me::Resources::Dx12::Shader::Shader(std::string const& a_path, Renderer::Dx12::RenderLayerDx12& a_renderLayer) : ShaderBase()
{
    m_vertShader = a_path;
	m_pixShader = a_path;

    auto r = &a_renderLayer;
    if(r != nullptr)
    {
        m_renderLayer = r;
        LoadShader();
    }
}

void Me::Resources::Dx12::Shader::LoadShader()
{
	std::wstring vShader = std::wstring(m_vertShader.begin(), m_vertShader.end());
	std::wstring pShader = std::wstring(m_pixShader.begin(), m_pixShader.end());

	CreateSignature();

	CreateVertexShader(vShader.c_str());
	CreatePixelShader(pShader.c_str());
	CreatePSO();

}

Me::Resources::Dx12::Shader::~Shader()
{
	m_pso.ReleaseAndGetAddressOf();

	for (auto s : m_shaders)
	{
		s.second.ReleaseAndGetAddressOf();
	}

	m_signature.ReleaseAndGetAddressOf();
}

void Me::Resources::Dx12::Shader::Reload()
{
    Unload();

	LoadShader();
}

void Me::Resources::Dx12::Shader::Unload()
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
}

void Me::Resources::Dx12::Shader::Bind()
{
    auto cmd = m_renderLayer->GetCmd();

	cmd.GetList()->SetPipelineState(m_pso.Get());
	cmd.GetList()->SetGraphicsRootSignature(m_signature.Get());
}

void Me::Resources::Dx12::Shader::UnBind()
{

}

void Me::Resources::Dx12::Shader::CreateVertexShader(const wchar_t* a_path)
{
	D3D12_SHADER_BYTECODE vs = {};

	ID3DBlob* vertexShader;
	ID3DBlob* errorBuff;
	HRESULT hr = D3DCompileFromFile(a_path,
		nullptr,
		nullptr,
		"VS",
		"vs_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShader,
		&errorBuff);

	if(FAILED(hr))
	{
		ME_GFX_ASSERT_M(false, "Failed to load Shader!", Files::FileSystem::GetFileName(a_path))
	}
	vs.BytecodeLength = vertexShader->GetBufferSize();
	vs.pShaderBytecode = vertexShader->GetBufferPointer();

	m_shaders[ShaderType::VertexShader] = vertexShader;
}
void Me::Resources::Dx12::Shader::CreatePixelShader(const wchar_t* a_path)
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

void Me::Resources::Dx12::Shader::CreateSignature()
{
	CD3DX12_DESCRIPTOR_RANGE texTable;
	texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0);

	CD3DX12_ROOT_PARAMETER  rootParameters[3];
	rootParameters[0].InitAsDescriptorTable(1, &texTable, D3D12_SHADER_VISIBILITY_PIXEL);
	rootParameters[1].InitAsConstantBufferView(0);
	rootParameters[2].InitAsShaderResourceView(1, 1);

	auto staticSamplers = GetStaticSamplers();

	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(_countof(rootParameters),
		rootParameters,
		static_cast<unsigned int>(staticSamplers.size()),
		staticSamplers.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* signature;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr);

	m_renderLayer->GetDevice().GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_signature));
}
void Me::Resources::Dx12::Shader::CreatePSO()
{
    std::vector< D3D12_INPUT_ELEMENT_DESC> vLayout;
    vLayout.push_back(
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        );
	vLayout.push_back(		
    	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		);
	vLayout.push_back(		
    	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		);

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};

	inputLayoutDesc.NumElements = static_cast<UINT>(vLayout.size());
	inputLayoutDesc.pInputElementDescs = vLayout.data();

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
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.SampleDesc = { 1, 0 };
	psoDesc.SampleMask = 0xffffffff;
	CD3DX12_RASTERIZER_DESC rDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	rDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	rDesc.CullMode = D3D12_CULL_MODE_NONE;
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

	D3D12_DEPTH_STENCIL_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));

	depthDesc.DepthEnable = TRUE;
	depthDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	depthDesc.StencilEnable = FALSE;

	psoDesc.DepthStencilState = depthDesc;

	m_renderLayer->GetDevice().GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pso));
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> Me::Resources::Dx12::Shader::GetStaticSamplers()
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
