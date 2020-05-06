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
			void SetPosition(float[2]);
			void SetPosition(math::Vec2);
			void SetSize(float,float);
			void SetSize(float[2]);
			void SetSize(math::Vec2);
			void SetRotation(float);

			void SetColour(math::Vec3) override;
			void SetColour(math::Vec4) override;

			void UseShader(const char*) override;
			void UseShader(std::string) override;

			void UseTexture(const char*) override;
			void UseTexture(std::string) override;

			void SetUV(float, float, float, float);
			void SetUV(float[4]);
			void SetUV(math::Vec4);

			math::Vec3 GetPos() const override;
			math::Vec3 GetSize() const override;
			math::Vec3 GetRotation() const override;

			void Submit(renderer::Renderer&) override;
		};
	}
}