#pragma once

#include <math.h>

namespace meduza
{
	namespace math
	{
#pragma region Vec2

		class Vec2
		{
		public:
#pragma warning(push)
#pragma warning(disable : 4201)
			union
			{
				float m_xy[2];

				struct
				{
					float m_x;
					float m_y;
				};
			};
#pragma warning(pop)

			Vec2()
			{
				m_xy[0] = m_xy[1] = 0;
			}
			Vec2(float a_x, float a_y) 
			{
				m_xy[0] = a_x;
				m_xy[1] = a_y;
			}

			inline Vec2& operator=(const Vec2& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];

				return *this;
			}

			inline Vec2& operator+=(const Vec2& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];

				return *this;
			}
			inline Vec2& operator-=(const Vec2& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];

				return *this;
			}
			inline Vec2& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;

				return *this;
			}
			inline Vec2& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;

				return *this;
			}

			inline float operator[](int a_index) const
			{
				if (a_index == 0 || a_index == 1)
				{
					return m_xy[a_index];
				}
				else
				{
					return -1;
				}
			}
			inline float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1)
				{
					return m_xy[a_index];
				}
				else
				{
					static_assert(1, "index out of range");
					return m_xy[a_index];
				}
			}

			inline float dot(Vec2 const& a_rhs) const
			{
				return (m_xy[0] * a_rhs[0] + m_xy[1] * a_rhs[1]);
			}
			Vec2& normalize()
			{
				float l = length();
				*this = Vec2(m_xy[0] / l, m_xy[1] / l);
				return *this;
			}
			inline float length() const
			{
				float sqRoot = (float)sqrt(m_xy[0] * m_xy[0] + m_xy[1] * m_xy[1]);
				return sqRoot;
			}
		};

		Vec2 operator+(const Vec2& a_lhs, const Vec2& a_rhs);
		Vec2 operator-(const Vec2& a_lhs, const Vec2& a_rhs);
		Vec2 operator*(const Vec2& a_lhs, float a_rhs);
		Vec2 operator/(const Vec2& a_lhs, float a_rhs);
		bool operator==(const Vec2& a_lhs, const Vec2& a_rhs);
		bool operator!=(const Vec2& a_lhs, const Vec2& a_rhs);

#pragma endregion

	}
}