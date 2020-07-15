#include "mePch.h"
#include "Meduza/Transform.h"

meduza::Transform::Transform()
{
	Identity();
}

meduza::Transform::Transform(math::Vec3 a_trans, math::Vec3 a_scale)
{
	Identity();
	SetPosition(a_trans);
	SetScale(a_scale);
}

meduza::math::Vec3 meduza::Transform::Position() const
{
	return math::Vec3(m_transform[3], m_transform[7], m_transform[11]);
}

meduza::math::Vec2 meduza::Transform::SetPosition(const math::Vec2& a_rhs)
{
	m_transform[3] = a_rhs.m_x;
	m_transform[7] = a_rhs.m_y;

	return a_rhs;
}

meduza::math::Vec3 meduza::Transform::SetPosition(const math::Vec3& a_rhs)
{
	m_transform[3] = a_rhs.m_x;
	m_transform[7] = a_rhs.m_y;
	m_transform[11] = a_rhs.m_z;

	return a_rhs;
}

meduza::math::Vec3 meduza::Transform::Scale() const
{
	return math::Vec3(m_transform[0] / m_unitsPerPixel, m_transform[5] / m_unitsPerPixel, m_transform[10] / m_unitsPerPixel);
}

meduza::math::Vec3 meduza::Transform::GetPixelScale() const
{
	return math::Vec3(m_transform[0], m_transform[5], m_transform[10]);
}

meduza::math::Vec2 meduza::Transform::SetScale(const math::Vec2& a_rhs)
{
	m_transform[0] = a_rhs.m_x * m_unitsPerPixel;
	m_transform[5] = a_rhs.m_y * m_unitsPerPixel;

	return a_rhs;
}

meduza::math::Vec3 meduza::Transform::SetScale(const math::Vec3& a_rhs)
{
	m_transform[0] = a_rhs.m_x * m_unitsPerPixel;
	m_transform[5] = a_rhs.m_y * m_unitsPerPixel;
	m_transform[10] = a_rhs.m_z * m_unitsPerPixel;
	return a_rhs;
}

void meduza::Transform::SetUnitsPerPixel(const float a_uPP)
{
	math::Vec3 scale = Scale();
	m_unitsPerPixel = a_uPP;
	SetScale(scale);
}

void meduza::Transform::Identity()
{
	for (int i = 0; i < sizeof(m_transform) / sizeof(float); i++)
	{
		m_transform[i] = 0;
	}

	m_transform[0] = 1; m_transform[5] = 1; m_transform[10] = 1; m_transform[15] = 1;
}
