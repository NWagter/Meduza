#include "mePch.h"

#include "Core/Drawable/Sprite.h"
#include "Util/MeduzaHelper.h"

meduza::drawable::Sprite::Sprite()
{
	m_drawData = new DrawData();
}

meduza::drawable::Sprite::Sprite(float a_pos[2], float a_size[2], float a_z, Texture&)
{
	m_drawData = new DrawData();
	m_drawData->m_position = glm::vec3(a_pos[0], a_pos[1], 0);
	m_drawData->m_size = glm::vec3(a_size[0], a_size[1], 0);
	m_drawData->m_rotation = glm::vec3(0, 0, a_z);

}

meduza::drawable::Sprite::~Sprite()
{
}

void meduza::drawable::Sprite::SetPosition(float a_x, float a_y)
{
	m_drawData->m_size = glm::vec3(a_x, a_y, 0);
}

void meduza::drawable::Sprite::SetPostion(float a_pos[2])
{
	m_drawData->m_position = glm::vec3(a_pos[0], a_pos[1], 0);
}

void meduza::drawable::Sprite::SetPostion(math::Vec2 a_pos)
{
	m_drawData->m_position = glm::vec3(a_pos.m_x, a_pos.m_y, 0);
}

void meduza::drawable::Sprite::SetSize(float a_x,float a_y)
{
	m_drawData->m_size = glm::vec3(a_x, a_y, 0);
}

void meduza::drawable::Sprite::SetSize(float a_size[2])
{
	m_drawData->m_size = glm::vec3(a_size[0], a_size[1], 0);
}

void meduza::drawable::Sprite::SetSize(math::Vec2 a_size)
{
	m_drawData->m_size = glm::vec3(a_size.m_x, a_size.m_y, 1);
}

void meduza::drawable::Sprite::SetRotation(float a_z)
{
	m_drawData->m_rotation = glm::vec3(0, 0, a_z);
}

void meduza::drawable::Sprite::Submit(renderer::Renderer& a_renderer)
{
	Drawable::Submit(a_renderer);
}
