#include "cepch.h"
#include "Platform/Windows/DX12_CommandQueue.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_Fence.h"
#include "Platform/Windows/DX12_CommandList.h"

cr::DX12_CommandQueue::DX12_CommandQueue(D3D12_COMMAND_QUEUE_DESC a_desc, DX12_Device& a_device)
{
	m_fence = new DX12_Fence(a_device);

	a_device.GetDevice()->CreateCommandQueue(
		&a_desc,
		IID_PPV_ARGS(&m_queue));
}

cr::DX12_CommandQueue::~DX12_CommandQueue()
{
	m_queue.ReleaseAndGetAddressOf();
	delete m_fence;
}

void cr::DX12_CommandQueue::ExecuteList(DX12_CommandList * a_list)
{
	a_list->Close();

	ID3D12CommandList* const commandLists[] = {
		a_list->GetList()
	};

	m_queue->ExecuteCommandLists(_countof(commandLists), commandLists);
}

void cr::DX12_CommandQueue::Flush()
{
	m_fence->Flush(*this);
}
