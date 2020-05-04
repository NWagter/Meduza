#pragma once

#include "Drawable.h"

namespace meduza
{
	class Texture;

	namespace drawable
	{
		class Sprite : public Drawable
		{
		public:
			Sprite();
			Sprite(float[2], float[2], float, Texture&);
			~Sprite() override;

			void SetPosition(float,float);
			void SetPostion(float[2]);
			void SetPostion(math::Vec2);
			void SetSize(float,float);
			void SetSize(float[2]);
			void SetSize(math::Vec2);
			void SetRotation(float);

			void UseShader(const char*) override;
			void UseShader(std::string) override;

			math::Vec3 GetPos() const override;
			math::Vec3 GetSize() const override;
			math::Vec3 GetRotation() const override;

			void Submit(renderer::Renderer&) override;
		};
	}
}