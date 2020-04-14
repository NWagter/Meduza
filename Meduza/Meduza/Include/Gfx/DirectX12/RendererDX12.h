#pragma once

#include "Core/Renderer.h"

namespace meduza
{
	namespace renderer
	{
		class RendererDX12 : public Renderer
		{
		public:
			RendererDX12();
			~RendererDX12() override;

			void Clear(Colour) override;

			void Draw(Sprite) override;
			void Draw(Mesh) override;
			void Draw(Text) override;

			void Render() override;
		};
	}
}