#pragma once

#include "../Common/CommandQueue.h"

class Dx12_Fence;
class Dx12_Device;
class Dx12_CommandList;

class Dx12_CommandQueue: public CommandQueue {
public:
	Dx12_CommandQueue(D3D12_COMMAND_QUEUE_DESC, const Dx12_Device&);

	ID3D12CommandQueue* GetQueue();
	virtual void ExecuteList(Dx12_CommandList* a_lists);
	void Flush();

private:

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
	Dx12_Fence* m_fence;
};