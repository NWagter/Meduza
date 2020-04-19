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

			void Submit(renderer::Renderer&);
		};
	}
}