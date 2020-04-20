#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	struct DrawData;

	enum class Type
	{
		None = 0,
		Sprite,
		UI,
		Model,
	};

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
			inline virtual Type GetDrawType() { return m_drawType; }
		protected:
			DrawData* m_drawData = nullptr;
			Type m_drawType = Type::None;
		};
	}
}