#include "MePCH.h"
#include "Math/Vector2.h"

#include "Math/Vector3.h"

Me::Math::Vector2::Vector2(const Me::Math::Vector3& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;
}

Me::Math::Vector2& Me::Math::Vector2::operator=(const Me::Math::Vector3& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;

	return *this;
}