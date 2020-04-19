#pragma once

#include "Core/MeduzaUtil.h"

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
			static Renderer* CreateRenderer(API, Window&);
			virtual ~Renderer() = default;

			virtual void Clear(Colour) = 0;

			virtual void Submit(drawable::Drawable*) = 0;
			
			virtual void Submit(std::vector<drawable::Drawable*>) = 0;

			virtual void Render() = 0;
		};
	}
}