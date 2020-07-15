#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"

#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"

meduza::renderer::DescriptorDx12::DescriptorDx12(D3D12_DESCRIPTOR_HEAP_DESC a_desc)
{
	auto device = RendererDx12::GetRenderer()->GetContext().GetDevice();
	device->GetDevice()->CreateDescriptorHeap(&a_desc, IID_PPV_ARGS(m_heap.GetAddressOf()));
	m_heapSize = device->GetDevice()->GetDescriptorHandleIncrementSize(a_desc.Type);
}

meduza::renderer::DescriptorDx12::~DescriptorDx12()
{
	m_heap.ReleaseAndGetAddressOf();
}
