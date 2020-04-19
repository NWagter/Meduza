#pragma once

#include "Gfx/Core/Renderer.h"

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

			void Draw(drawable::Drawable*) override;

			void Render() override;

		private:
			Window* m_window;
		};
	}
}