#pragma once

#include "Core/Renderer.h"

namespace meduza
{
	namespace renderer
	{
		class RendererOpenGL : public Renderer
		{
		public:
			RendererOpenGL();
			~RendererOpenGL();

			void Clear(float[]) override;

			void Draw(Sprite) override;
			void Draw(Mesh) override;
			void Draw(Text) override;

			void Render() override;
		};
	}
}