#include "mePch.h"

#include "Core/Core.h"

#include "Gfx/Animator.h"
#include "Gfx/Animation.h"

bool meduza::gfx::Animator::Exists(std::string a_name)
{
	for (auto a : m_animations)
	{
		if (a->GetName() == a_name)
		{
			return true;
		}
	}

	return false;
}
