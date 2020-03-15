#pragma once

#include "Gfx/RenderLayer.h"

namespace mr {

	class Window;

	class DX12_Renderlayer : public RenderLayer {
	public:
		DX12_Renderlayer(Window&);

		virtual void Clear(float[4]) override;
		virtual void Update() override;
		virtual void Render() override;

	private:
		Window* m_window;
	};
}