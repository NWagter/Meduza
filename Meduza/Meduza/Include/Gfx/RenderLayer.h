#pragma once

#include "Gfx/GFXHelper.h"

namespace cr { class IDrawable; }

namespace cr {
	enum class RenderAPI {
		None,
		DX12,
		NVN
	};

	class Window;

	class RenderLayer {
	public:
		virtual ~RenderLayer() = default;
		static RenderLayer* CreateRenderLayer(Window&);

		virtual void Clear(float[4]) = 0;
		virtual void Render() = 0;
		virtual void Draw(IDrawable*) = 0; // Require a Drawable which contains data : Transform, VertexBuffer, IndexBuffer, Material etc.
		virtual void Update(float) = 0;
		virtual void InitImGui() = 0;
		static RenderAPI GetUsedAPI();
	};
}