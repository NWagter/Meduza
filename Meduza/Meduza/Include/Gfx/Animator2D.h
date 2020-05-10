#pragma once

#include "Animator.h"
#include "Animation2D.h"

namespace meduza
{
	namespace drawable
	{
		class Sprite;
	}

	namespace gfx
	{
		class Animator2D : public Animator
		{
		public:
			Animator2D(drawable::Sprite&);
			~Animator2D() override;
			virtual void Play() override;
			virtual void SetAnimation(std::string) override;

			void CreateAnimation2D(std::string, float, std::string);
			Animation2D& GetAnimation(std::string);
		private:
			drawable::Sprite* m_sprite;
		};
	}
}