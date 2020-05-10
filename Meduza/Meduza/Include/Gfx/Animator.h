#pragma once

#include "Util/Timer.h"

namespace meduza
{
	namespace gfx
	{
		class Animation;

		class Animator
		{
		public:
			virtual ~Animator() = default;
			virtual void SetAnimation(std::string) = 0;
			virtual void Play() = 0;

			bool Exists(std::string);

		protected:
			meduza::utils::Timer<float> m_timer;

			std::vector<Animation*> m_animations;
			std::string m_currentAnimation = "";

			bool m_isPlaying = false;
		};
	}
}