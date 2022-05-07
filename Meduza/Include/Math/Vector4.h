#pragma once

namespace Me
{
	namespace Math
	{
		class Vector4
		{
		public:
#pragma warning(push)
#pragma warning(disable : 4201)
			union
			{
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
			inline Vector4()
			{
				m_x = m_y = m_z = m_w = 0;
			}
			inline Vector4(float a_x, float a_y, float a_z, float a_w)
			{
				m_x = a_x;
				m_y = a_y;
				m_z = a_z;
				m_w = a_w;
			}
			inline Vector4(float a_vec4[4])
			{
				m_x = a_vec4[0];
				m_y = a_vec4[1];
				m_z = a_vec4[2];
				m_w = a_vec4[3];
			}
			inline Vector4(Vector3 const a_vec3, float a_w)
			{
				m_x = a_vec3[0];
				m_y = a_vec3[1];
				m_z = a_vec3[2];
				m_w = a_w;
			}

			inline Vector4& operator=(const Vector4& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];
				m_z = a_rhs[2];
				m_w = a_rhs[3];

				return *this;
			}
			inline Vector4& operator=(const Vector3& a_rhs);
			inline Vector4& operator+=(const Vector4& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];
				m_z = m_z + a_rhs[2];
				m_w = m_w + a_rhs[3];

				return *this;
			}
			inline Vector4& operator-=(const Vector4& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];
				m_z = m_z - a_rhs[2];
				m_w = m_w - a_rhs[3];

				return *this;
			}
			inline Vector4& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;
				m_z = m_z * a_rhs;
				m_w = m_w * a_rhs;

				return *this;
			}
			inline Vector4& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;
				m_z = m_z / a_rhs;
				m_w = m_w / a_rhs;

				return *this;
			}

			inline Vector4 operator+(const Vector4& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z + a_rhs.m_z;
				float w = m_w + a_rhs.m_w;

				return Vector4(x, y, z, w);
			}
			inline Vector4 operator-(const Vector4& a_rhs)
			{
				float x = m_x - a_rhs.m_x;
				float y = m_y - a_rhs.m_y;
				float z = m_z - a_rhs.m_z;
				float w = m_w - a_rhs.m_w;

				return Vector4(x, y, z, w);
			}
			inline Vector4 operator*(const Vector4& a_rhs)
			{
				float x = m_x * a_rhs.m_x;
				float y = m_y * a_rhs.m_y;
				float z = m_z * a_rhs.m_z;
				float w = m_w * a_rhs.m_w;

				return Vector4(x, y, z, w);
			}
			inline Vector4 operator/(const Vector4& a_rhs)
			{
				float x = m_x / a_rhs.m_x;
				float y = m_y / a_rhs.m_y;
				float z = m_z / a_rhs.m_z;
				float w = m_w / a_rhs.m_w;

				return Vector4(x, y, z, w);
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
					printf("Can't acces index %i in a vec 4!\n", a_index);
					return m_xyzw[0];
				}
			}

			inline float Lenght()
			{
				return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
			}
		};

		inline bool operator==(Vector4 a_rhs, Vector4 a_lhs);
		inline bool operator!=(Vector4 a_rhs, Vector4 a_lhs);
	}
}

#include "Math/Vector4.inl"