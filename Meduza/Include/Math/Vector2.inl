#include "Math/Vector2.h"

namespace Me
{
	namespace Math
	{
		inline bool operator==(Vector2 a_rhs, Vector2 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y)
			{
				return false;
			}

			return true;
		}
		inline bool operator!=(Vector2 a_rhs, Vector2 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y)
			{
				return true;
			}

			return false;
		}
	
		inline float Distance(Vector2 a_rhs, Vector2 a_lhs)
		{
			float x = a_lhs.m_x - a_rhs.m_x;
			float y = a_lhs.m_y - a_rhs.m_y;

			return abs(sqrtf(x * x + y * y));
		}
		inline Vector2 Direction(Vector2 a_origin, Vector2 a_destination)
		{
			return a_destination - a_origin;
		}
	
		inline Vector2 Lerp(Vector2 a_rhs, Vector2 a_lhs, float a_delta)
		{
			float x = (1 - a_delta) * a_rhs.m_x + a_delta * a_lhs.m_x;
			float y = (1 - a_delta) * a_rhs.m_y + a_delta * a_lhs.m_y;

			return Math::Vector2(x, y);
		}
		inline Vector2 MoveTowards(Vector2 a_rhs, Vector2 a_lhs, float a_delta)
		{
			Math::Vector2 returnValue;

			returnValue.m_x = MoveTowards(a_rhs.m_x, a_lhs.m_x, a_delta);
			returnValue.m_y = MoveTowards(a_rhs.m_y, a_lhs.m_y, a_delta);

			return returnValue;
		}

		inline float DotProduct(Vector2 const& a_rhs, Vector2 const& a_lhs)
		{
			float const x = a_rhs.m_x * a_lhs.m_x;
			float const y = a_rhs.m_y * a_lhs.m_y;

			float const dotProduct = x + y;

			return dotProduct;
		}
	}
}