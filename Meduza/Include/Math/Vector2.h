#pragma once

namespace Me
{
	namespace Math
	{
		class Vector3;

		class Vector2
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
				};
				float m_xy[2];
			};
#pragma warning(pop)
			inline Vector2()
			{
				m_x = m_y = 0;
			}
			inline Vector2(float a_x, float a_y)
			{
				m_x = a_x;
				m_y = a_y;
			}
			inline Vector2(int a_x, int a_y)
			{
				m_x = static_cast<float>(a_x);
				m_y = static_cast<float>(a_y);
			}
			Vector2(const Vector3& a_rhs);

			Vector2& operator=(const Vector3& a_rhs);
			inline Vector2& operator=(const Vector2& a_rhs)
			{
				m_x = a_rhs[0];
				m_y = a_rhs[1];

				return *this;
			}

			inline Vector2& operator+=(const Vector2& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];

				return *this;
			}
			inline Vector2& operator*=(const Vector2& a_rhs)
			{
				m_x = m_x * a_rhs[0];
				m_y = m_y * a_rhs[1];

				return *this;
			}
			inline Vector2& operator-=(const Vector2& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];

				return *this;
			}
			inline Vector2& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;

				return *this;
			}
			inline Vector2& operator/=(float a_rhs)
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
					printf("Can't acces index %i in a vec 2!\n", a_index);
					return m_xy[0];
				}
			}

			inline Vector2 operator+(const Vector2& a_rhs) const
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;

				return Vector2(x, y);
			}
			inline Vector2 operator-(const Vector2& a_rhs) const
			{
				float x = m_x - a_rhs.m_x;
				float y = m_y - a_rhs.m_y;

				return Vector2(x, y);
			}
			inline Vector2 operator*(float a_rhs) const
			{
				float x = m_x * a_rhs;
				float y = m_y * a_rhs;

				return Vector2(x, y);
			}
			inline Vector2 operator/(float a_rhs) const
			{
				float x = m_x / a_rhs;
				float y = m_y / a_rhs;

				return Vector2(x, y);
			}

			inline float Lenght() const
			{
				return std::sqrt(m_x * m_x + m_y * m_y);
			}
			inline float Distance(Vector2 a_rhs) const
			{
				float x = a_rhs.m_x - m_x;
				float y = a_rhs.m_y - m_y;

				return std::abs(std::sqrt(x * x + y * y));
			}

			inline Vector2& ABS()
			{
				m_x = std::abs(m_x);
				m_y = std::abs(m_y);

				return *this;
			}
			inline Vector2& Normalize()
			{
				float lenght = Lenght();

				m_x = m_x / lenght;
				m_y = m_y / lenght;

				return *this;
			}

			inline Vector2& Floor()
			{
				m_x = std::floor(m_x);
				m_y = std::floor(m_y);

				return *this;
			}
			inline Vector2& Ceil()
			{
				m_x = std::ceil(m_x);
				m_y = std::ceil(m_y);

				return *this;
			}
		};

		inline bool operator==(Vector2 a_rhs, Vector2 a_lhs);
		inline bool operator!=(Vector2 a_rhs, Vector2 a_lhs);

		inline float Distance(Vector2 a_rhs, Vector2 a_lhs);
		inline Vector2 Direction(Vector2 a_origin, Vector2 a_destination);

		inline Vector2 Lerp(Vector2 a_rhs, Vector2 a_lhs, float a_delta);
		inline Vector2 MoveTowards(Vector2 a_rhs, Vector2 a_lhs, float a_delta);

		inline float DotProduct(Vector2 const& a_rhs, Vector2 const& a_lhs);
	}
}

#include "Math/Vector2.inl"