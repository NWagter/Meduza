#pragma once

namespace cr {

	class WinWindow;
	class DX12_Device;
	class DX12_CommandQueue;
	class DX12_Descriptor;

	class DX12_SwapChain {
	public:
		DX12_SwapChain(DX12_Device&, WinWindow&, DX12_CommandQueue&);
		~DX12_SwapChain();

		inline Microsoft::WRL::ComPtr<IDXGISwapChain4> GetSwapChain() { return m_swapChain; }
		inline ID3D12Resource* GetCurrentBuffer() { return m_frameBuffer[m_currentframeBufferIndex].Get(); }
		inline Microsoft::WRL::ComPtr<ID3D12Resource> GetBuffers(int a_id) { return m_frameBuffer[a_id]; }

		void ClearRTV();
		void CreateRTV(DX12_Device&, DX12_Descriptor&);
		void Resize(int,int);
		void Present();

		inline DXGI_FORMAT GetFormat() { return m_backBufferFormat; }
		inline const HWND GetHWND() { return m_hwnd; }
		inline const unsigned int GetCurrentFrameIndex() { return m_currentframeBufferIndex; }

		private:
			void CreateSwapChain();

			Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
			Microsoft::WRL::ComPtr<ID3D12Resource> m_frameBuffer[gs_numBuffers];
			DX12_Device* m_device;
			DX12_CommandQueue* m_queue;
			DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

			unsigned int m_currentframeBufferIndex = 0;

			HWND m_hwnd;
			WinWindow* m_window;
	};
}