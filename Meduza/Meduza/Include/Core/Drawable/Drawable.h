#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	class Shader;
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
			virtual ~Drawable() = default;

			virtual void UseShader(const char*) = 0;
			virtual void UseShader(std::string) = 0;

			virtual math::Vec3 GetPos() const = 0;
			virtual math::Vec3 GetSize() const = 0;
			virtual math::Vec3 GetRotation() const = 0;

			DrawData* GetDrawData() { return m_drawData; }
			inline virtual Type GetDrawType() { return m_drawType; }

			virtual void Submit(renderer::Renderer&);
		protected:

			DrawData* m_drawData = nullptr;
			Type m_drawType = Type::None;
		};
	}
}