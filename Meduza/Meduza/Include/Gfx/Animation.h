#pragma once

#include <string>

namespace meduza
{
	namespace gfx
	{
		class Animation
		{
		public:
			Animation() = default;
			Animation(std::string, float);
			virtual ~Animation() = default;

			virtual void OnStart() = 0;
			virtual void OnEnd() = 0;

			inline std::string GetName() const { return m_animationName; }
			inline float GetCycleTime() const { return m_cycleSpeed; }
		protected:
			std::string m_animationName;
			float m_cycleSpeed;
		};
	}
}