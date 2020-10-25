#include "MePCH.h"
#include "Math/MeduzaMath.h"

Me::Math::Vec2& Me::Math::Vec2::operator=(const Vec3& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;

	return *this;
}

Me::Math::Vec3& Me::Math::Vec3::operator=(const Vec2& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;

	return *this;
}

Me::Math::Vec4& Me::Math::Vec4::operator=(const Vec3& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;
	m_z = a_rhs.m_z;

	return *this;
}
