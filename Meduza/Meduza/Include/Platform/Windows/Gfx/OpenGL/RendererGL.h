#pragma once

#include "Platform/General/Renderer.h"

namespace meduza
{

	namespace renderer
	{
		class RendererGL : public Renderer
		{
		public:
			RendererGL();
			~RendererGL() override;

			void Clear(Colour) override;
			void SwapBuffers() override;

			void Draw(drawable::Drawable*) override;
			void Submit(std::vector<drawable::Drawable*>) override;

		};
	}

}