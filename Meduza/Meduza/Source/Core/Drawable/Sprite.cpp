#include "mePch.h"

#include "Util/MeduzaHelper.h"

#include "Drawable/Sprite.h"

#include "Platform/General/Gfx/ShaderLibrary.h"

meduza::drawable::Sprite::Sprite()
{
	m_drawType = Type::Sprite;
	m_drawData = new DrawData();
	m_drawData->m_shaderId = ShaderLibrary::GetShader("DefaultShader")->GetId();
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
	delete m_drawData;
}

void meduza::drawable::Sprite::SetPosition(float a_x, float a_y)
{
	m_drawData->m_position = glm::vec3(a_x, a_y, 0);
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

void meduza::drawable::Sprite::UseShader(const char* a_name)
{
	m_drawData->m_shaderId = ShaderLibrary::GetShader(a_name)->GetId();
}

void meduza::drawable::Sprite::UseShader(std::string a_name)
{
	m_drawData->m_shaderId = ShaderLibrary::GetShader(a_name)->GetId();
}

meduza::math::Vec3 meduza::drawable::Sprite::GetPos() const
{
	return math::Vec3(m_drawData->m_position.x, m_drawData->m_position.y, m_drawData->m_position.z);
}

meduza::math::Vec3 meduza::drawable::Sprite::GetSize() const
{
	return math::Vec3(m_drawData->m_size.x, m_drawData->m_size.y, m_drawData->m_size.z);
}

meduza::math::Vec3 meduza::drawable::Sprite::GetRotation() const
{
	return math::Vec3(m_drawData->m_rotation.x, m_drawData->m_rotation.y, m_drawData->m_rotation.z);
}

void meduza::drawable::Sprite::Submit(renderer::Renderer& a_renderer)
{
	Drawable::Submit(a_renderer);
}
