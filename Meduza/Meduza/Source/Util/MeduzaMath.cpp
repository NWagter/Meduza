#include "Util/MeduzaMath.h"

meduza::math::Vec2 meduza::math::operator+(const Vec2& a_lhs, const Vec2& a_rhs)
{
	return Vec2(a_lhs[0] + a_rhs[0], a_lhs[1] + a_rhs[1]);
}

meduza::math::Vec2 meduza::math::operator-(const Vec2& a_lhs, const Vec2& a_rhs)
{
	return Vec2(a_lhs[0] - a_rhs[0], a_lhs[1] - a_rhs[1]);
}

meduza::math::Vec2 meduza::math::operator*(const Vec2& a_lhs, float a_rhs)
{
	return Vec2(a_lhs[0] * a_rhs, a_lhs[1] * a_rhs);

}

meduza::math::Vec2 meduza::math::operator/(const Vec2& a_lhs, float a_rhs)
{
	return Vec2(a_lhs[0] / a_rhs, a_lhs[1] / a_rhs);
}

bool meduza::math::operator==(const Vec2& a_lhs, const Vec2& a_rhs)
{
	if (a_lhs[0] == a_rhs[0] && a_lhs[1] == a_rhs[1])
		return true;
	return false;
}

bool meduza::math::operator!=(const Vec2& a_lhs, const Vec2& a_rhs)
{
	if (a_lhs[0] != a_rhs[0] || a_lhs[1] != a_rhs[1])
		return true;
	return false;
}
