#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/DepthStencilDx12.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"

meduza::renderer::DepthStencilDx12::DepthStencilDx12(int a_w, int a_h)
{
	D3D12_DESCRIPTOR_HEAP_DESC dvsDesc = {};
	dvsDesc.NumDescriptors = 1;
	dvsDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dvsDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dvsDesc.NodeMask = 0;

	m_dsv = new DescriptorDx12(dvsDesc);
	SetBuffer(a_w, a_h);
}

meduza::renderer::DepthStencilDx12::~DepthStencilDx12()
{
	delete m_dsv;
	m_dsBuffer.ReleaseAndGetAddressOf();
}

D3D12_CPU_DESCRIPTOR_HANDLE meduza::renderer::DepthStencilDx12::DepthStencilView() const
{
	return m_dsv->GetHeap()->GetCPUDescriptorHandleForHeapStart();
}

void meduza::renderer::DepthStencilDx12::SetBuffer(int a_w, int a_h)
{
	auto device = RendererDx12::GetRenderer()->GetContext().GetDevice()->GetDevice();
	auto cmd = RendererDx12::GetRenderer()->GetCmd();

	m_dsBuffer.Reset();

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = a_w;
	depthStencilDesc.Height = a_h;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = m_dsFormat;
	depthStencilDesc.SampleDesc = { 1, 0 };
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = m_dsFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CD3DX12_HEAP_PROPERTIES prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(m_dsBuffer.GetAddressOf()));

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	device->CreateDepthStencilView(m_dsBuffer.Get(), nullptr, DepthStencilView());


	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_dsBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
	// Transition the resource from its initial state to be used as a depth buffer.
	cmd.GetList()->ResourceBarrier(1, &barrier);
}

