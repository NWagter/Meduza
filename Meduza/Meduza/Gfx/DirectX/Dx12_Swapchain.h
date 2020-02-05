#pragma once
#include "../Common/Swapchain.h"

class Dx12_Device;
class Dx12_Descriptor;
class Dx12_CommandQueue;

class Dx12_Swapchain : public Swapchain {

public:
	Dx12_Swapchain(const Dx12_Device&, HWND, Dx12_CommandQueue&);
	virtual void CreateSwapchain(unsigned int, unsigned int) override;


	Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D12Resource> GetCurrentBuffer();
	Microsoft::WRL::ComPtr<ID3D12Resource> m_swapChainBuffer[gs_frameBufferCount];

	void UpdateRTVView(const Dx12_Device&, Dx12_Descriptor&);
	void Present();

	DXGI_FORMAT GetFormat();
	const HWND GetHWND();
	const unsigned int GetCurrentFrameIndex();
private:
	const Dx12_Device* m_device;
	Dx12_CommandQueue* m_queue;
	DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	unsigned int m_currentframeBufferIndex = 0;

	HWND m_hwnd;
};