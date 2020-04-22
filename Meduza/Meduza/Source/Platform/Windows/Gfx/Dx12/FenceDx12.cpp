#include "mePch.h"

#include "Platform/Windows/Gfx/Dx12/FenceDx12.h"

#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandQueueDx12.h"

meduza::renderer::FenceDx12::FenceDx12(DeviceDx12& a_device)
{
	a_device.GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
}

meduza::renderer::FenceDx12::~FenceDx12()
{
	m_fence.ReleaseAndGetAddressOf();
}

void meduza::renderer::FenceDx12::WaitForFence(UINT a_fValue)
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

void meduza::renderer::FenceDx12::Flush(CommandQueueDx12& a_queue)
{
	m_currentFence++;
	a_queue.GetQueue()->Signal(m_fence.Get(), m_currentFence);

	WaitForFence(m_currentFence);
}
