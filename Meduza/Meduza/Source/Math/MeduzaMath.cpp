#include "mePch.h"
#include "Math/MeduzaMath.h"

meduza::math::Vec2& meduza::math::Vec2::operator=(const Vec3& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;

	return *this;
}

meduza::math::Vec3& meduza::math::Vec3::operator=(const Vec2& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;

	return *this;
}

meduza::math::Vec4& meduza::math::Vec4::operator=(const Vec3& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;
	m_z = a_rhs.m_z;

	return *this;
}
