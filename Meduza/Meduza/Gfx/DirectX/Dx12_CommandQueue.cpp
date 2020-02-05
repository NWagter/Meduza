#include "pch/pch.h"
#include "Dx12_CommandQueue.h"

#include "Dx12_CommandList.h"
#include "Dx12_Fence.h"
#include "Dx12_Device.h"

Dx12_CommandQueue::Dx12_CommandQueue(D3D12_COMMAND_QUEUE_DESC a_desc, const Dx12_Device& a_device)
{
	m_fence = new Dx12_Fence(a_device);

	ThrowIfFailed(a_device.m_device->CreateCommandQueue(
		&a_desc,
		IID_PPV_ARGS(&m_commandQueue)));

}

ID3D12CommandQueue* Dx12_CommandQueue::GetQueue()
{
	return m_commandQueue.Get();
}

void Dx12_CommandQueue::ExecuteList(Dx12_CommandList* a_list)
{
	a_list->Close();

	ID3D12CommandList* const commandLists[] = {
		a_list->GetList()
	};

	m_commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);
}

void Dx12_CommandQueue::Flush()
{
	m_fence->Flush(*this);
}
