#pragma once
class Fence {
public:
	virtual void InitilizeFence() = 0;
	virtual void WaitForFence(UINT a_fvalue) = 0;
};