#include "mePch.h"

#include "Gfx/Animation.h"

meduza::gfx::Animation::Animation(std::string a_name, float a_speed)
{
	m_animationName = a_name;
	m_cycleSpeed = a_speed;
}
