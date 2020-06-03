#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	class Shader;
	class Texture;
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

			virtual void SetColour(math::Vec3) = 0;
			virtual void SetColour(math::Vec4) = 0;

			virtual void UseShader(const char*) = 0;
			virtual void UseShader(std::string) = 0;
			virtual void UseShader(meduza::Shader&) = 0;

			virtual void UseTexture(const char*) = 0;
			virtual void UseTexture(std::string) = 0;
			virtual void UseTexture(meduza::Texture&) = 0;

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