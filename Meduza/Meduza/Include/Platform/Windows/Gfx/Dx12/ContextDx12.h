#pragma once

#include "Util/MeduzaHelper.h"

#include "Platform/General/Context.h"



namespace meduza
{
	namespace renderer
	{
		class DeviceDx12;
		class CommandQueueDx12;
		class DescriptorDx12;

		class ContextDx12 : public Context
		{
		public:
			ContextDx12(HWND);
			~ContextDx12() override;

			void SwapBuffer() override;
			void Resize(math::Vec2) override;

			inline DeviceDx12* GetDevice() { return m_device; }
			inline CommandQueueDx12* GetQueue() { return m_queue; }

			inline Microsoft::WRL::ComPtr<IDXGISwapChain4> GetSwapChain() { return m_swapChain; }
			inline ID3D12Resource* GetCurrentBuffer() { return m_frameBuffer[m_currentframeBufferIndex].Get(); }
			inline Microsoft::WRL::ComPtr<ID3D12Resource> GetBuffers(int a_id) { return m_frameBuffer[a_id]; }

			void ClearRTV();
			void CreateRTV(DescriptorDx12&);
			void Resize(int, int);

			inline DXGI_FORMAT GetFormat() { return m_backBufferFormat; }
			inline HWND GetHWND() const { return m_hwnd; }
			inline unsigned int GetCurrentFrameIndex() const { return m_currentframeBufferIndex; }

		private:
			math::Vec2 m_size;
			bool m_resize = false;
			void CreateSwapChain();

			Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
			Microsoft::WRL::ComPtr<ID3D12Resource> m_frameBuffer[GS_FRAMEBUFFERS];

			DeviceDx12* m_device;
			CommandQueueDx12* m_queue;
			DescriptorDx12* m_rtv;

			DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

			unsigned int m_currentframeBufferIndex = 0;

			HWND m_hwnd;
		};
	}
}
