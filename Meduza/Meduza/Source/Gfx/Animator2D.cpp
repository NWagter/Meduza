#include "mePch.h"

#include "Core/Core.h"

#include "Gfx/Animator2D.h"
#include "Gfx/Animation2D.h"

meduza::gfx::Animator2D::Animator2D(Renderable2D& a_renderable)
{
	m_renderable = &a_renderable;
}

meduza::gfx::Animator2D::~Animator2D()
{
	for (auto a : m_animations)
	{
		delete a;
	}
	m_animations.clear();
}

void meduza::gfx::Animator2D::Play()
{
	if (m_isPlaying && m_timer.IsFinished())
	{
		auto anim = dynamic_cast<Animation2D*>(&GetAnimation(m_currentAnimation));
		if (m_renderable != nullptr) 
		{
			anim->UpdateFrame(*m_renderable);
		}
		m_timer.Start(anim->GetCycleTime());
	}
}

void meduza::gfx::Animator2D::SetAnimation(std::string a_anim)
{
	if (m_currentAnimation == a_anim)
	{
		return;
	}

	auto anim = &GetAnimation(a_anim);

	if (m_isPlaying)
	{
		GetAnimation(m_currentAnimation).OnEnd();
		m_currentAnimation = a_anim;
	}

	anim->OnStart();
	m_currentAnimation = a_anim;

	m_timer.Start(anim->GetCycleTime());
	m_isPlaying = true;

	if (m_renderable != nullptr)
	{
		anim->UpdateFrame(*m_renderable);
	}
}

void meduza::gfx::Animator2D::CreateAnimation2D(std::string a_name, float a_speed, meduza::Texture& a_texture)
{
	if (Exists(a_name))
	{
		ME_GFX_LOG("Animation : %s exists already!", a_name.c_str());
		return;
	}

	m_animations.push_back(new Animation2D(a_name, a_speed, a_texture));
}

void meduza::gfx::Animator2D::CreateAnimation2D(std::string a_name, float a_speed, std::string a_textureName)
{
	if (Exists(a_name))
	{
		ME_GFX_LOG("Animation : %s exists already!", a_name.c_str());
		return;
	}

	m_animations.push_back(new Animation2D(a_name, a_speed, a_textureName));
}

meduza::gfx::Animation2D& meduza::gfx::Animator2D::GetAnimation(std::string a_name)
{
	for (auto a : m_animations)
	{
		if (a->GetName() == a_name)
		{
			return dynamic_cast<Animation2D&>(*a);
		}
	}

	ME_GFX_ASSERT_M(0, "Animation doesn't exits %s", a_name.c_str())
		return dynamic_cast<Animation2D&>(*m_animations[0]);
}
