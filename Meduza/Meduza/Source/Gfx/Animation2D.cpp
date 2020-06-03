#include "mePch.h"

#include "Core/Core.h"

#include "Gfx/Animation2D.h"
#include "Platform/General/Gfx/TextureLibrary.h"
#include "Drawable/Sprite.h"

meduza::gfx::Animation2D::Animation2D(std::string a_name, float a_speed, Texture& a_texture): Animation(a_name,a_speed)
{
	m_texture = &a_texture;

	m_currentFrame = 0;
	m_frameCount = 0;
}

meduza::gfx::Animation2D::Animation2D(std::string a_name, float a_speed, std::string a_textureName) : Animation(a_name, a_speed)
{
	m_textureName = a_textureName;
	m_texture = meduza::TextureLibrary::GetTexture(a_textureName);

	m_currentFrame = 0;
	m_frameCount = 0;
}

meduza::gfx::Animation2D::~Animation2D()
{
}

void meduza::gfx::Animation2D::AddFrame(math::Vec4 a_rect)
{
	Frame newFrame{ m_frameCount, a_rect };
	m_frames.push_back(newFrame);
	m_frameCount++;
}

void meduza::gfx::Animation2D::UpdateFrame(drawable::Sprite& a_sprite)
{
	if (m_frameCount == 0)
	{
		ME_GFX_LOG("NO Frames in animation : %s", m_animationName.c_str());
		return;
	}


	m_currentFrame++;
	if (m_currentFrame == m_frameCount)
	{
		m_currentFrame = 0;
	}

	a_sprite.SetUV(m_frames[m_currentFrame].m_frameRect);
}

void meduza::gfx::Animation2D::OnStart()
{
	m_currentFrame = 0;
}

void meduza::gfx::Animation2D::OnEnd()
{
	//Stop Timer
}
