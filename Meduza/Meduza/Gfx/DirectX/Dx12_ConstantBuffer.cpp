#include "pch/pch.h"
#include "Dx12_ConstantBuffer.h"

#include "Dx12_Device.h"
#include "Dx12_Descriptor.h"

Dx12_ConstantBuffer::Dx12_ConstantBuffer(const Dx12_Device& a_device, Dx12_Descriptor& a_cbvDescriptor)
{
	CD3DX12_HEAP_PROPERTIES props = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(1024 * 64);

	a_device.m_device->CreateCommittedResource(
		&props, // this heap will be used to upload the constant buffer data
		D3D12_HEAP_FLAG_NONE, // no flags
		&buffer, // size of the resource heap. Must be a multiple of 64KB for single-textures and constant buffers
		D3D12_RESOURCE_STATE_GENERIC_READ, // will be data that is read from so we keep it in the generic read state
		nullptr, // we do not have use an optimized clear value for constant buffers
		IID_PPV_ARGS(&m_cBufferResource));
	m_cBufferResource->SetName(L"Constant Buffer Upload Resource Heap");

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = m_cBufferResource->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (sizeof(ConstantBuffer) + 255) & ~255;    // CB size is required to be 256-byte aligned.
	a_device.m_device->CreateConstantBufferView(&cbvDesc, a_cbvDescriptor.GetHeap()->GetCPUDescriptorHandleForHeapStart());

	ZeroMemory(&m_constBufferData, sizeof(m_constBufferData));

	CD3DX12_RANGE readRange(0, 0);    // We do not intend to read from this resource on the CPU. (End is less than or equal to begin)
	m_cBufferResource->Map(0, &readRange, reinterpret_cast<void**>(&m_bufferDataGPUAdress));
	memcpy(m_bufferDataGPUAdress, &m_constBufferData, sizeof(m_constBufferData));
}

void Dx12_ConstantBuffer::CopyData(int a_alignment)
{
	memcpy(m_bufferDataGPUAdress + a_alignment, &m_constBufferData, sizeof(m_constBufferData));
}
