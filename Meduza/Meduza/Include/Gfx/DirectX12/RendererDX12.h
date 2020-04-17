#pragma once

#include "Core/Renderer.h"

namespace meduza
{
	class Window;

	namespace renderer
	{
		class DeviceDX12;

		class RendererDX12 : public Renderer
		{
		public:
			RendererDX12(Window&);
			~RendererDX12() override;

			void Clear(Colour) override;

			void Draw(Sprite) override;
			void Draw(Mesh) override;
			void Draw(Text) override;

			void Render() override;

		private:
			DeviceDX12* m_device;
			Window* m_window;
		};
	}
}