#pragma once

namespace meduza
{
	namespace renderer
	{
		class Renderer;
	}

	namespace drawable
	{
		class Drawable
		{
		public:
			Drawable() = default;
			virtual ~Drawable() = default;

			virtual void Submit(renderer::Renderer&);
		};
	}
}