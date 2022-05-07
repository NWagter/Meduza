#pragma once

namespace Me
{
	namespace Math
	{
		class Vector3
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
				};

				struct
				{
					float m_roll;
					float m_yaw;
					float m_pitch;
				};

				float m_xyz[3];
			};
#pragma warning(pop)
			inline Vector3()
			{
				m_x = m_y = m_z = 0;
			}
			inline Vector3(float a_x, float a_y, float a_z)
			{
				m_x = a_x;
				m_y = a_y;
				m_z = a_z;
			}
			inline Vector3(float a_value)
			{
				m_x = a_value;
				m_y = a_value;
				m_z = a_value;
			}


			inline Vector3& operator=(const Vector3& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];
				m_z = a_rhs[2];

				return *this;
			}
			inline Vector3& operator=(const Vector2& a_rhs);
			inline Vector3& operator+=(const Vector3& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];
				m_z = m_z + a_rhs[2];

				return *this;
			}
			inline Vector3& operator+=(const Vector2& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];

				return *this;
			}
			inline Vector3& operator-=(const Vector3& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];
				m_z = m_z - a_rhs[2];

				return *this;
			}
			inline Vector3& operator*=(const Vector3& a_rhs)
			{
				m_x = m_x * a_rhs[0];
				m_y = m_y * a_rhs[1];
				m_z = m_z * a_rhs[2];

				return *this;
			}
			inline Vector3& operator/=(float a_rhs)
			{
				m_x = m_x / a_rhs;
				m_y = m_y / a_rhs;
				m_z = m_z / a_rhs;

				return *this;
			}

			inline Vector3 operator+(float a_rhs)
			{
				float x = m_x + a_rhs;
				float y = m_y + a_rhs;
				float z = m_z + a_rhs;

				return Vector3(x, y, z);
			}
			inline Vector3& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;
				m_z = m_z * a_rhs;

				return *this;
			}
			inline Vector3 operator*(float  a_rhs)
			{
				float x = m_x * a_rhs;
				float y = m_y * a_rhs;
				float z = m_z * a_rhs;

				return Vector3(x, y, z);
			}
			inline Vector3 operator+(const Vector3& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z + a_rhs.m_z;

				return Vector3(x, y, z);
			}
			inline Vector3 operator+(const Vector2& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z;

				return Vector3(x, y, z);
			}
			inline Vector3 operator-(const Vector3& a_rhs)
			{
				float x = m_x - a_rhs.m_x;
				float y = m_y - a_rhs.m_y;
				float z = m_z - a_rhs.m_z;

				return Vector3(x, y, z);
			}
			inline Vector3 operator*(const Vector3& a_rhs)
			{
				float x = m_x * a_rhs.m_x;
				float y = m_y * a_rhs.m_y;
				float z = m_z * a_rhs.m_z;

				return Vector3(x, y, z);
			}
			inline Vector3 operator/(const Vector3& a_rhs)
			{
				float x = m_x / a_rhs.m_x;
				float y = m_y / a_rhs.m_y;
				float z = m_z / a_rhs.m_z;

				return Vector3(x, y, z);
			}

			inline float operator[](int a_index) const
			{
				if (a_index == 0 || a_index == 1 || a_index == 2)
					return m_xyz[a_index];
				else {
					return 0;
				}
			}
			inline float& operator[](int a_index)
			{
				if (a_index == 0 || a_index == 1 || a_index == 2)
					return m_xyz[a_index];
				else {
					printf("Can't acces index %i in a vec 3!\n", a_index);
					return m_xyz[0];
				}
			}

			inline float Lenght()
			{
				return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
			}

			inline Vector3& Round()
			{
				float lenght = Lenght();

				m_x = std::round(m_x);
				m_y = std::round(m_y);
				m_z = std::round(m_z);

				return *this;
			}
			inline Vector3& Floor()
			{
				float lenght = Lenght();

				m_x = std::floor(m_x);
				m_y = std::floor(m_y);
				m_z = std::floor(m_z);

				return *this;
			}
			inline Vector3& Ceil()
			{
				float lenght = Lenght();

				m_x = std::ceil(m_x);
				m_y = std::ceil(m_y);
				m_z = std::ceil(m_z);

				return *this;
			}

			inline float Distance(Vector3 a_rhs)
			{
				float x = a_rhs.m_x - m_x;
				float y = a_rhs.m_y - m_y;
				float z = a_rhs.m_z - m_z;
				return abs(sqrtf(x * x + y * y + z * z));
			}
			
			inline Vector3& Normalize()
			{
				float lenght = Lenght();

				m_x = m_x / lenght;
				m_y = m_y / lenght;
				m_z = m_z / lenght;

				return *this;
			}
			inline Vector3& Inverse()
			{
				m_x = -m_x;
				m_y = -m_y;
				m_z = -m_z;

				return *this;
			}

			inline bool IsNan()
			{
				int i = 0;
				if (std::isnan(m_x))
				{
					i++;
				}
				if (std::isnan(m_y))
				{
					i++;
				}
				if (std::isnan(m_z))
				{
					i++;
				}

				return i == 3;
			}
		};

		inline bool operator==(Vector3 a_rhs, Vector3 a_lhs);
		inline bool operator!=(Vector3 a_rhs, Vector3 a_lhs);

		inline float Distance(Vector3 a_rhs, Vector3 a_lhs);
		inline Vector3 Direction(Vector3 a_origin, Vector3 a_destination);

		inline Vector3 Lerp(Vector3 a_rhs, Vector3 a_lhs, float a_delta);
		inline Vector3 MoveTowards(Vector3 a_rhs, Vector3 a_lhs, float a_delta);

		inline Vector3 LookAtRotation(Vector3 a_target, Vector3 a_origin);

		inline float DotProduct(Vector3 const& a_rhs, Vector3 const& a_lhs);
		inline Vector3 CrossProduct(Vector3 const& a_rhs, Vector3 const& a_lhs);
		inline Vector3 TrippleCrossProduct(Vector3 const& a_vecA, Vector3 const& a_vecB, Vector3 const& a_vecC);

		inline Vector3 Inverse(Vector3 const& a_rhs);

		namespace Random
		{
			inline Vector3 RandomRange(const Vector3 a_min, const Vector3 a_max);
		}
	}
}

#include "Math/Vector3.inl"