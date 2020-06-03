#include "mePch.h"

#include "Platform/General/Utils/MeduzaHelper.h"

#include "Platform/Windows/Gfx/Dx12/CommandQueueDx12.h"

#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/FenceDx12.h"

meduza::renderer::CommandQueueDx12::CommandQueueDx12(D3D12_COMMAND_QUEUE_DESC a_desc, DeviceDx12& a_device)
{
	m_fence = new FenceDx12(a_device);
	m_description = a_desc;

	a_device.GetDevice()->CreateCommandQueue(
		&m_description,
		IID_PPV_ARGS(&m_queue));
}

meduza::renderer::CommandQueueDx12::~CommandQueueDx12()
{
	m_queue.ReleaseAndGetAddressOf();
	delete m_fence;
}

void meduza::renderer::CommandQueueDx12::ExecuteList(CommandListDx12* a_list)
{
	a_list->Close();

	ID3D12CommandList* const commandLists[] =
	{
		a_list->GetList()
	};

	m_queue->ExecuteCommandLists(_countof(commandLists), commandLists);
}

void meduza::renderer::CommandQueueDx12::Flush()
{
	m_fence->Flush(*this);
}
