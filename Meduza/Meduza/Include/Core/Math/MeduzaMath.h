#pragma once

#include <math.h>

namespace meduza
{
	namespace math
	{
		class Vec3;
		class Vec4;

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
			inline Vec2()
			{
				m_x = m_y = 0;
			}
			inline Vec2(float a_x, float a_y)
			{
				m_x = a_x;
				m_y = a_y;
			}

			inline Vec2& operator=(const Vec2& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];

				return *this;
			}
			inline Vec2& operator=(const Vec3& a_rhs);
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
					return m_xy[a_index];
				else {
					return 0;
				}
			}
			inline float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1)
					return m_xy[a_index];
				else {
					static_assert(1, "index out of range");
					return m_xy[a_index];
				}
			}

			inline Vec2 operator+(const Vec2& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;

				return Vec2(x, y);
			}
			inline Vec2 operator-(const Vec2& a_rhs)
			{
				float x = m_x - a_rhs.m_x;
				float y = m_y - a_rhs.m_y;

				return Vec2(x, y);
			}
			inline Vec2 operator*(float a_rhs)
			{
				float x = m_x * a_rhs;
				float y = m_y * a_rhs;

				return Vec2(x,y);
			}
			inline Vec2 operator/(float a_rhs)
			{
				float x = m_x / a_rhs;
				float y = m_y / a_rhs;

				return Vec2(x, y);
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
			inline Vec3()
			{
				m_x = m_y = m_z = 0;
			}
			inline Vec3(float a_x, float a_y, float a_z)
			{
				m_x = a_x;
				m_y = a_y;
				m_z = a_z;
			}


			inline Vec3& operator=(const Vec3& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];
				m_z = a_rhs[2];

				return *this;
			}
			inline Vec3& operator=(const Vec2& a_rhs);
			inline Vec3& operator+=(const Vec3& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];
				m_z = m_z + a_rhs[2];

				return *this;
			}
			inline Vec3& operator-=(const Vec3& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];
				m_z = m_z - a_rhs[2];

				return *this;
			}
			inline Vec3& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;
				m_z = m_z * a_rhs;

				return *this;
			}
			inline Vec3& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;
				m_z = m_z / a_rhs;

				return *this;
			}

			inline float operator[](int a_index) const
			{
				if (a_index == 0 || a_index == 1 || a_index == 2)
					return m_xyz[a_index];
				else {
					
					
					("Can't acces index %i in a vec 2!\n", a_index);
					return 0;
				}
			}
			inline float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1 || a_index == 2)
					return m_xyz[a_index];
				else {
					static_assert(1, "index out of range");
					return m_xyz[a_index];
				}
			}
			
			inline Vec3 operator+(const Vec3& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z + a_rhs.m_z;

				return Vec3(x, y, z);
			}
			inline Vec3 operator-(const Vec3& a_rhs)
			{
				float x = m_x - a_rhs.m_x;
				float y = m_y - a_rhs.m_y;
				float z = m_z - a_rhs.m_z;

				return Vec3(x, y, z);
			}
			inline Vec3 operator*(const Vec3& a_rhs)
			{
				float x = m_x * a_rhs.m_x;
				float y = m_y * a_rhs.m_y;
				float z = m_z * a_rhs.m_z;

				return Vec3(x, y, z);
			}
			inline Vec3 operator/(const Vec3& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z / a_rhs.m_z;

				return Vec3(x, y, z);
			}
		};

		class Vec4
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
					float m_w;
				};
				struct
				{
					float m_r;
					float m_g;
					float m_b;
					float m_a;
				};
				float m_xyzw[4];
			};
#pragma warning(pop)
			inline Vec4()
			{
				m_x = m_y = m_z = m_w = 0;
			}
			inline Vec4(float a_x, float a_y, float a_z, float a_w)
			{
				m_x = a_x;
				m_y = a_y;
				m_z = a_z;
				m_w = a_w;
			}

			inline Vec4& operator=(const Vec4& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];
				m_z = a_rhs[2];
				m_w = a_rhs[3];

				return *this;
			}
			inline Vec4& operator=(const Vec3& a_rhs);
			inline Vec4& operator+=(const Vec4& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];
				m_z = m_z + a_rhs[2];
				m_w = m_w + a_rhs[3];

				return *this;
			}
			inline Vec4& operator-=(const Vec4& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];
				m_z = m_z - a_rhs[2];
				m_w = m_w - a_rhs[3];

				return *this;
			}
			inline Vec4& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;
				m_z = m_z * a_rhs;
				m_w = m_w * a_rhs;

				return *this;
			}
			inline Vec4& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;
				m_z = m_z / a_rhs;
				m_w = m_w / a_rhs;

				return *this;
			}
			
			inline float operator[](int a_index) const
			{
				if (a_index == 0 || a_index == 1 || a_index == 2 || a_index == 3)
					return m_xyzw[a_index];
				else {
					return 0;
				}
			}
			inline float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1 || a_index == 2 || a_index == 3)
					return m_xyzw[a_index];
				else {
					static_assert(1, "index out of range");
					return m_xyzw[a_index];
				}
			}

			inline Vec4 operator+(const Vec4& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z + a_rhs.m_z;
				float w = m_w + a_rhs.m_w;

				return Vec4(x, y, z, w);
			}
			inline Vec4 operator-(const Vec4& a_rhs)
			{
				float x = m_x - a_rhs.m_x;
				float y = m_y - a_rhs.m_y;
				float z = m_z - a_rhs.m_z;
				float w = m_w - a_rhs.m_w;

				return Vec4(x, y, z, w);
			}
			inline Vec4 operator*(const Vec4& a_rhs)
			{
				float x = m_x * a_rhs.m_x;
				float y = m_y * a_rhs.m_y;
				float z = m_z * a_rhs.m_z;
				float w = m_w * a_rhs.m_w;

				return Vec4(x, y, z, w);
			}
			inline Vec4 operator/(const Vec4& a_rhs)
			{
				float x = m_x / a_rhs.m_x;
				float y = m_y / a_rhs.m_y;
				float z = m_z / a_rhs.m_z;
				float w = m_w / a_rhs.m_w;

				return Vec4(x, y, z, w);
			}
		};

// =========== Operators

		inline bool operator==(Vec2 a_rhs, Vec2 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y)
			{
				return false;
			}

			return true;
		}
		inline bool operator!=(Vec2 a_rhs, Vec2 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y)
			{
				return true;
			}

			return false;
		}

		inline bool operator==(Vec3 a_rhs, Vec3 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z)
			{
				return false;
			}

			return true;
		}
		inline bool operator!=(Vec3 a_rhs, Vec3 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z)
			{
				return true;
			}

			return false;
		}
		
		inline bool operator==(Vec4 a_rhs, Vec4 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z || a_rhs.m_w != a_lhs.m_w)
			{
				return false;
			}

			return true;
		}
		inline bool operator!=(Vec4 a_rhs, Vec4 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z || a_rhs.m_w != a_lhs.m_w)
			{
				return true;
			}

			return false;
		}
	}
}