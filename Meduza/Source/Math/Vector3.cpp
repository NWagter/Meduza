#include "MePCH.h"
#include "Math/Vector3.h"

#include "Math/Vector2.h"

Me::Math::Vector3& Me::Math::Vector3::operator=(const Vector2& a_rhs)
{
	m_x = a_rhs.m_x;
	m_y = a_rhs.m_y;

	return *this;
}