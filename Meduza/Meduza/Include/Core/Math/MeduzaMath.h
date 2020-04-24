#pragma once

#include <math.h>

namespace meduza
{
	namespace math
	{
		class Vec2
		{
		public:
#pragma warning(push)
#pragma warning(disable : 4201)
			union {
				struct
				{
					float m_x;
					float m_y;
				};
				float m_xy[2];
			};
#pragma warning(pop)
			Vec2()
			{
				m_x = m_y = 0;
			}
			Vec2(float a_x, float a_y)
			{
				m_x = a_x;
				m_y = a_y;
			}

			Vec2& operator=(const Vec2& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];

				return *this;
			}

			Vec2& operator+=(const Vec2& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];

				return *this;
			}
			Vec2& operator-=(const Vec2& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];

				return *this;
			}
			Vec2& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;

				return *this;
			}
			Vec2& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;

			}
			float operator[](int a_index) const
			{
				if (a_index == 0 || a_index == 1)
					return m_xy[a_index];
				else {
					return 0;
				}
			}
			float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1)
					return m_xy[a_index];
				else {
					static_assert(1, "index out of range");
					return m_xy[a_index];
				}
			}
		};

		class Vec3
		{
		public:
#pragma warning(push)
#pragma warning(disable : 4201)
			union {
				struct
				{
					float m_x;
					float m_y;
					float m_z;
				};
				float m_xyz[3];
			};
#pragma warning(pop)
			Vec3()
			{
				m_x = m_y = m_z = 0;
			}
			Vec3(float a_x, float a_y, float a_z)
			{
				m_x = a_x;
				m_y = a_y;
				m_z = a_z;
			}


			Vec3& operator=(const Vec3& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];
				m_z = a_rhs[2];

				return *this;
			}

			Vec3& operator+=(const Vec3& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];
				m_z = m_z + a_rhs[2];

				return *this;
			}
			Vec3& operator-=(const Vec3& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];
				m_z = m_z - a_rhs[2];

				return *this;
			}
			Vec3& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;
				m_z = m_z * a_rhs;

				return *this;
			}
			Vec3& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;
				m_z = m_z / a_rhs;

				return *this;
			}


			float operator[](int a_index) const
			{
				if (a_index == 0 || a_index == 1 || a_index == 2)
					return m_xyz[a_index];
				else {
					printf("Can't acces index %i in a vec 2!\n", a_index);
					return 0;
				}
			}
			float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1 || a_index == 2)
					return m_xyz[a_index];
				else {
					static_assert(1, "index out of range");
					return m_xyz[a_index];
				}
			}
		};
	}
}