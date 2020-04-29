#pragma once

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
		class Context;

		class Renderer
		{
		public:

			struct RendererData
			{
				renderer::Renderer* renderer = nullptr;
				Window* window = nullptr;
			};

			static RendererData* CreateRenderer(API, math::Vec2);
			virtual ~Renderer() = default;
			
			virtual void Clear(Colour) = 0;
			virtual void SwapBuffers() = 0;

			virtual void Draw(drawable::Drawable*) = 0;
			virtual void Submit(std::vector<drawable::Drawable*>) = 0;

			virtual void EnableOptick() {};
		};
	}
}