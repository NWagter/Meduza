#pragma once

#include "MeduzaUtil.h"

#include "Math/MeduzaMath.h"

namespace meduza
{
	class Window;

	namespace drawable
	{
		class Drawable;
	}

	namespace renderer
	{
		class Renderer
		{
		public:
			static Renderer* CreateRenderer(API, math::Vec2);
			virtual ~Renderer() = default;
			
			virtual void Clear(Colour) = 0;
			virtual void SwapBuffers() = 0;

			virtual void Draw(drawable::Drawable*) = 0;
			virtual void Submit(std::vector<drawable::Drawable*>) = 0;

			Window& GetWindow() const;

		protected:
			static Window* m_window;
		};
	}
}