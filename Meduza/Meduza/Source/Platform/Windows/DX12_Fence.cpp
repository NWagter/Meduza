#include <cepch.h>

#include "Platform/Windows/DX12_Fence.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_CommandQueue.h"

cr::DX12_Fence::DX12_Fence(cr::DX12_Device& a_device)
{
	a_device.GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
}

cr::DX12_Fence::~DX12_Fence()
{
	m_fence.ReleaseAndGetAddressOf();
}

void cr::DX12_Fence::WaitForFence(UINT a_fvalue)
{
	std::chrono::milliseconds duration = std::chrono::milliseconds::max();

	if (m_fence->GetCompletedValue() < a_fvalue)
	{
		HANDLE fencehandle = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		m_fence->SetEventOnCompletion(a_fvalue, fencehandle);
		::WaitForSingleObject(fencehandle, static_cast<DWORD>(duration.count()));

		CloseHandle(fencehandle);
	}
}

void cr::DX12_Fence::Flush(DX12_CommandQueue& a_queue)
{
	m_currentFence++;
	a_queue.GetQueue()->Signal(m_fence.Get(), m_currentFence);

	WaitForFence(m_currentFence);
}
