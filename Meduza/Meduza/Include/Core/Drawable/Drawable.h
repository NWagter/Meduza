#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	struct DrawData;

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
			virtual ~Drawable();

			virtual void Submit(renderer::Renderer&);

			DrawData* GetDrawData() { return m_drawData; }
		protected:
			DrawData* m_drawData = nullptr;
		};
	}
}