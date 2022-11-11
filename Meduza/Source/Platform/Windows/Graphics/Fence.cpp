#include "MePCH.h"

#include "Platform/Windows/Graphics/Fence.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandQueue.h"

Me::Renderer::Dx12::Fence::Fence(Device* a_device)
{
	a_device->GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
}

Me::Renderer::Dx12::Fence::~Fence()
{
	WaitForFence(m_currentFence);
	m_fence.ReleaseAndGetAddressOf();
}

void Me::Renderer::Dx12::Fence::WaitForFence(UINT const a_fValue)
{
	std::chrono::milliseconds duration = std::chrono::milliseconds::max();

	if (m_fence->GetCompletedValue() < a_fValue)
	{
		HANDLE fencehandle = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		m_fence->SetEventOnCompletion(a_fValue, fencehandle);
		::WaitForSingleObject(fencehandle, static_cast<DWORD>(duration.count()));

		CloseHandle(fencehandle);
	}
}

void Me::Renderer::Dx12::Fence::Flush(CommandQueue& a_queue)
{
	m_currentFence++;
	a_queue.GetQueue()->Signal(m_fence.Get(), m_currentFence);

	WaitForFence(m_currentFence);
}