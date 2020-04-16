#pragma once

#include "MeduzaUtil.h"

namespace meduza
{
	class Window;

	namespace renderer
	{
		class Renderer
		{
		public:
			static Renderer* CreateRenderer(API, Window&);
			virtual ~Renderer() = default;

			virtual void Clear(Colour) = 0;

			virtual void Draw(Sprite) = 0;
			virtual void Draw(Mesh) = 0;
			virtual void Draw(Text) = 0;

			virtual void Render() = 0;
		};
	}
}