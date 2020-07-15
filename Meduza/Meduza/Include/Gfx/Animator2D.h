#pragma once

#include "Animator.h"
#include "Animation2D.h"

namespace meduza
{
	namespace gfx
	{
		class Animator2D : public Animator
		{
		public:
			// Sprite to Animate
			Animator2D() = default;
			Animator2D(Renderable2D&);
			~Animator2D() override;
			virtual void Play() override;
			// Animation Name
			virtual void SetAnimation(std::string) override;

			// Name of Animation, Animation Speed (seconds), Texture
			void CreateAnimation2D(std::string, float, Texture&);
			void CreateAnimation2D(std::string, float, std::string);
			Animation2D& GetAnimation(std::string);
			
			// Sprite to Animate
			inline void SetSprite(Renderable2D& a_renderable) { m_renderable = &a_renderable; }
		private:
			Renderable2D* m_renderable = nullptr;
		};
	}
}