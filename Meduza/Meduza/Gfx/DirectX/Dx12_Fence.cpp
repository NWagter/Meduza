#include "pch/pch.h"
#include "Dx12_Fence.h"

#include "Dx12_Device.h"
#include "Dx12_CommandQueue.h"

Dx12_Fence::Dx12_Fence(const Dx12_Device& a_device)
{
	ThrowIfFailed(a_device.m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
}

void Dx12_Fence::InitilizeFence()
{
}

void Dx12_Fence::WaitForFence(UINT a_singleValue)
{
    std::chrono::milliseconds duration = std::chrono::milliseconds::max();

    if (m_fence->GetCompletedValue() < a_singleValue)
    {
        HANDLE m_fencehandle = CreateEvent(NULL, FALSE, FALSE, NULL);
        ThrowIfFailed(m_fence->SetEventOnCompletion(a_singleValue, m_fencehandle));
        ::WaitForSingleObject(m_fencehandle, static_cast<DWORD>(duration.count()));

        CloseHandle(m_fencehandle);
    }
}

void Dx12_Fence::Flush(Dx12_CommandQueue& a_queue)
{
    m_currentFence++;
    ThrowIfFailed(a_queue.GetQueue()->Signal(m_fence.Get(), m_currentFence));

    WaitForFence(m_currentFence);

}
