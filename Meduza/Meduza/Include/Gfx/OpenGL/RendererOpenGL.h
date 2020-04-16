#pragma once

#include "Core/Renderer.h"

namespace meduza
{
	class Window;

	namespace renderer
	{
		class RendererOpenGL : public Renderer
		{
		public:
			RendererOpenGL(Window&);
			void CreateContext();
			~RendererOpenGL() override;

			void Clear(Colour) override;

			void Draw(Sprite) override;
			void Draw(Mesh) override;
			void Draw(Text) override;

			void Render() override;

		private:
			Window* m_window;
		};
	}
}