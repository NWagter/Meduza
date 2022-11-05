#include "MePCH.h"

#include "Platform/Windows/Graphics/CommandQueue.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/Graphics/Fence.h"

Me::Renderer::Dx12::CommandQueue::CommandQueue(D3D12_COMMAND_QUEUE_DESC const a_desc, Device* a_device)
{
	m_fence = new Fence(a_device);
	m_description = a_desc;

	a_device->GetDevice()->CreateCommandQueue(&m_description, IID_PPV_ARGS(&m_queue));
}

Me::Renderer::Dx12::CommandQueue::~CommandQueue()
{
	m_queue.ReleaseAndGetAddressOf();
	delete m_fence;
}

void Me::Renderer::Dx12::CommandQueue::ExecuteList(CommandList* a_list)
{
	a_list->Close();

	ID3D12CommandList* const commandLists[] =
	{
		a_list->GetList()
	};

	m_queue->ExecuteCommandLists(_countof(commandLists), commandLists);
}

void Me::Renderer::Dx12::CommandQueue::Flush()
{
	m_fence->Flush(*this);
}