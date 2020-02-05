#pragma once
#include "../Common/Fence.h"

class Dx12_Device;
class Dx12_CommandQueue;

class Dx12_Fence : public Fence {

public :
	Dx12_Fence(const Dx12_Device&);

	virtual void InitilizeFence() override;	
	virtual void WaitForFence(UINT a_fvalue) override;

	void Flush(Dx12_CommandQueue&);


	Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
private:
	unsigned int m_currentFence = 0;
};