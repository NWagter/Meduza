#pragma once

#include "Gfx/RenderLayer.h"

namespace mr
{
	class WinWindow;

	class VK_RenderLayer : RenderLayer
	{
	public:
		VK_RenderLayer(Window&);
		~VK_RenderLayer();

		virtual void Clear(float[4]) override;
		virtual void PreRender() override;
		virtual void Render() override;

	private:

#ifdef PLATFORM_WINDOWS
		WinWindow* m_window;
#endif

	};
}