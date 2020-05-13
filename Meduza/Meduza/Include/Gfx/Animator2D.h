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
			// Sprite to Animate
			Animator2D() = default;
			Animator2D(drawable::Sprite&);
			~Animator2D() override;
			virtual void Play() override;
			// Animation Name
			virtual void SetAnimation(std::string) override;

			// Name of Animation, Animation Speed (seconds), Texture Name
			void CreateAnimation2D(std::string, float, std::string);
			Animation2D& GetAnimation(std::string);
			
			// Sprite to Animate
			inline void SetSprite(drawable::Sprite& a_sprite) { m_sprite = &a_sprite; }
		private:
			drawable::Sprite* m_sprite = nullptr;
		};
	}
}