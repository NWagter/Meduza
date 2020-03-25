#pragma once

#include "Gfx/RenderLayer.h"
#include "Gfx/GfxHelper.h"

namespace mr 
{

	class WinWindow;

	class DX12_Device;
	class DX12_Swapchain;
	class DX12_CommandList;
	class DX12_CommandQueue;
	class DX12_Descriptor;

	class DX12_Renderlayer : public RenderLayer
	{
	public:
		DX12_Renderlayer(Window&);
		virtual ~DX12_Renderlayer();
		virtual void Clear(float[4]) override;
		virtual void PreRender() override;
		virtual void Render() override;

	private:
		void EnableDebugLayer();
		void Resize();

		WinWindow* m_window;

		DX12_Device* m_device;
		DX12_Swapchain* m_swapChain;
		DX12_CommandQueue* m_cmdQueue;
		DX12_CommandList* m_cmdList;
		DX12_Descriptor* m_rtv;
		DX12_Descriptor* m_srv;
		DX12_Descriptor* m_cbv[gs_framebufferCount];

	};
}