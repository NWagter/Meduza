#pragma once

#include <cmath>

#define GETRADIUS(a_degree) (a_degree * 3.141592654f / 180)

namespace Me
{
	namespace Math
	{
		static constexpr float gs_pi = 3.141592654f;
		static constexpr float gs_pi2 = 6.283185307f;

		class Vec3;
		class Vec4;

		class Vec2
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
			inline Vec2()
			{
				m_x = m_y = 0;
			}
			inline Vec2(float a_x, float a_y)
			{
				m_x = a_x;
				m_y = a_y;
			}
			inline Vec2(int a_x, int a_y)
			{
				m_x = static_cast<float>(a_x);
				m_y = static_cast<float>(a_y);
			}

			Vec2(const Vec3& a_rhs);

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
					printf("Can't acces index %i in a vec 2!\n", a_index);
					return m_xy[0];
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

			inline float Lenght()
			{
				return sqrtf(m_x * m_x + m_y * m_y);
			}

			inline float Distance(Vec2 a_rhs)
			{
				float x = a_rhs.m_x - m_x;
				float y = a_rhs.m_y - m_y;

				return abs(sqrtf(x * x + y * y));
			}

			inline Vec2& ABS()
			{
				m_x = abs(m_x);
				m_y = abs(m_y);

				return *this;
			}

			inline Vec2& Normalize()
			{
				float lenght = Lenght();

				m_x = m_x / lenght;
				m_y = m_y / lenght;

				return *this;
			}

			inline Vec2& Floor()
			{
				m_x = floorf(m_x);
				m_y = floorf(m_y);

				return *this;
			}

			inline Vec2& Ceil()
			{
				m_x = ceilf(m_x);
				m_y = ceilf(m_y);
				
				return *this;
			}
		};

		class Vec3
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
			inline Vec3(float a_value)
			{
				m_x = a_value;
				m_y = a_value;
				m_z = a_value;
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
			
			inline Vec3& operator+=(const Vec2& a_rhs)
			{
				m_x = m_x + a_rhs[0];
				m_y = m_y + a_rhs[1];

				return *this;
			}

			inline Vec3& operator-=(const Vec3& a_rhs)
			{
				m_x = m_x - a_rhs[0];
				m_y = m_y - a_rhs[1];
				m_z = m_z - a_rhs[2];

				return *this;
			}			

			inline Vec3 operator+(float a_rhs)
			{				
				float x = m_x + a_rhs;
				float y = m_y + a_rhs;
				float z = m_z + a_rhs;

				return Vec3(x,y,z);
			}

			inline Vec3& operator*=(float a_rhs)
			{
				m_x = m_x * a_rhs;
				m_y = m_y * a_rhs;
				m_z = m_z * a_rhs;

				return *this;
			}

			inline Vec3 operator*(float a_rhs)
			{
				float x = m_x * a_rhs;
				float y = m_y * a_rhs;
				float z = m_z * a_rhs;

				return Vec3(x,y,z);
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
			
			inline Vec3 operator+(const Vec3& a_rhs)
			{
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z + a_rhs.m_z;

				return Vec3(x, y, z);
			}			
			
			inline Vec3 operator+(const Vec2& a_rhs)
			{				
				float x = m_x + a_rhs.m_x;
				float y = m_y + a_rhs.m_y;
				float z = m_z;

				return Vec3(x,y,z);
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
				float x = m_x / a_rhs.m_x;
				float y = m_y / a_rhs.m_y;
				float z = m_z / a_rhs.m_z;

				return Vec3(x, y, z);
			}

			inline float Lenght()
			{
				return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
			}

			inline float Distance(Vec3 a_rhs)
			{
				float x = a_rhs.m_x - m_x;
				float y = a_rhs.m_y - m_y;
				float z = a_rhs.m_z - m_z;
				return abs(sqrtf(x * x + y * y + z *z));
			}			

			inline Vec3& Normalize()
			{
				float lenght = Lenght();

				m_x = m_x / lenght;
				m_y = m_y / lenght;
				m_z = m_z / lenght;

				return *this;
			}

			inline Vec3& Inverse()
			{
				m_x = -m_x;
				m_y = -m_y;
				m_z = -m_z;
				
				return *this;
			}
		};

		class Vec4
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

			inline Vec4(float a_vec4[4])
			{
				m_x = a_vec4[0];
				m_y = a_vec4[1];
				m_z = a_vec4[2];
				m_w = a_vec4[3];
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
					printf("Can't acces index %i in a vec 4!\n", a_index);
					return m_xyzw[0];
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

			inline float Lenght()
			{
				return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
			}
		};


		class Mat4
		{
		public:
			#pragma warning(push)
#pragma warning(disable : 4201)
			union 
			{
				struct
				{
					float m_00, m_01, m_02, m_03;
					float m_10, m_11, m_12, m_13;
					float m_20, m_21, m_22, m_23;
					float m_30, m_31, m_32, m_33;
				};
				float m_mat[4][4];

				float m_m[4*4];
			};
#pragma warning(pop)
		public:
			Mat4(
				float a_00, float a_01, float a_02, float a_03,
				float a_10, float a_11, float a_12, float a_13,
				float a_20, float a_21, float a_22, float a_23,
				float a_30, float a_31, float a_32, float a_33)
			{
				m_00 = a_00; m_01 = a_01; m_02 = a_02; m_03 = a_03;
				m_10 = a_10; m_11 = a_11; m_12 = a_12; m_13 = a_13;
				m_20 = a_20; m_21 = a_21; m_22 = a_22; m_23 = a_23;
				m_30 = a_30; m_31 = a_31; m_32 = a_32; m_33 = a_33;			
			}

			Mat4()
			{
				*this = Identity();
			}

			inline float TriangleRule(	
						float a_01, float a_02, float a_03,
						float a_11, float a_12, float a_13,
						float a_21, float a_22, float a_23)
			{
					return  (a_01 * a_12 * a_23) +
							(a_02 * a_13 * a_21) +
							(a_03 * a_11 * a_22) -
							(a_03 * a_12 * a_21) -
							(a_01 * a_13 * a_22) -
							(a_02 * a_11 * a_23);
			}

			static inline Mat4 Identity()
			{
				return Mat4(1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);
			}
			inline Mat4& Inverse()
			{
				Mat4 temp = *this;

				temp.m_00 = TriangleRule(m_11, m_12, m_13,
					m_21, m_22, m_23,
					m_31, m_32, m_33);
				temp.m_10 = -TriangleRule(m_10, m_12, m_13,
					m_20, m_22, m_23,
					m_30, m_32, m_33);
				temp.m_20 = TriangleRule(m_10, m_11, m_13,
					m_20, m_21, m_23,
					m_30, m_31, m_33);
				temp.m_30 = -TriangleRule(m_10, m_11, m_12,
					m_20, m_21, m_22,
					m_30, m_31, m_32);

				//colum 1

				temp.m_01 = -TriangleRule(m_01, m_02, m_03,
					m_21, m_22, m_23,
					m_31, m_32, m_33);
				temp.m_11 = TriangleRule(m_00, m_02, m_03,
					m_20, m_22, m_23,
					m_30, m_32, m_33);
				temp.m_21 = -TriangleRule(m_00, m_01, m_03,
					m_20, m_21, m_23,
					m_30, m_31, m_33);
				temp.m_31 = TriangleRule(m_00, m_01, m_02,
					m_20, m_21, m_22,
					m_30, m_31, m_32);
				//colum 2

				temp.m_02 = TriangleRule(m_01, m_02, m_03,
					m_11, m_12, m_13,
					m_31, m_32, m_33);
				temp.m_12 = -TriangleRule(m_00, m_02, m_03,
					m_10, m_12, m_13,
					m_30, m_32, m_33);
				temp.m_22 = TriangleRule(m_00, m_01, m_03,
					m_10, m_11, m_13,
					m_30, m_31, m_33);
				temp.m_32 = -TriangleRule(m_00, m_01, m_02,
					m_10, m_11, m_12,
					m_30, m_31, m_32);

				//colum 3

				temp.m_03 = -TriangleRule(m_01, m_02, m_03,
					m_11, m_12, m_13,
					m_21, m_22, m_23);
				temp.m_13 = TriangleRule(m_00, m_02, m_03,
					m_10, m_12, m_13,
					m_20, m_22, m_23);
				temp.m_23 = -TriangleRule(m_00, m_01, m_03,
					m_10, m_11, m_13,
					m_20, m_21, m_23);
				temp.m_33 = TriangleRule(m_00, m_01, m_02,
					m_10, m_11, m_12,
					m_20, m_21, m_22);
				
				for(int i = 0; i < 16;i++)
				{
					m_m[i] = temp.m_m[i];
				}

				return *this;
			}
			
			inline Mat4& operator=(Mat4 a_rhs)
			{
				for(int i = 0; i < 16; i++)
					m_m[i] = a_rhs.m_m[i];

				return *this;
			}

			inline Mat4 operator +(const Mat4& a_rhs)
			{				
				Mat4 temp = *this;

				for (int i = 0; i < 16; i++)
				{
					temp.m_m[i] += a_rhs.m_m[i];
				}

				return temp;
			}

			inline Mat4 operator *(const Mat4& a_rhs)
			{
				Mat4 result = Mat4::Identity();
				Mat4 self = *this;

				for (auto i = 0; i < 4; ++i)
				{
					for (auto j = 0; j < 4; ++j)
					{
						result.m_mat[i][j] = 0.0f;

						for (auto k = 0; k < 4; ++k)
						{
							result.m_mat[i][j] += self.m_mat[i][k] * a_rhs.m_mat[k][j];
						}
					}
				}

				return result;
			}
			
			inline Mat4& operator*=(const Mat4 &a_rhs)
			{
				*this = *this * a_rhs;
				return *this;
			}

			inline Vec4 operator *(const Vec4& a_rhs)
			{
				Vec4 value;

				value.m_x = a_rhs.m_x * m_00 + a_rhs.m_x * m_10 + a_rhs.m_x * m_20 + a_rhs.m_x * m_30;
				value.m_y = a_rhs.m_y * m_01 + a_rhs.m_y * m_11 + a_rhs.m_y * m_21 + a_rhs.m_y * m_31;
				value.m_z = a_rhs.m_z * m_02 + a_rhs.m_z * m_12 + a_rhs.m_z * m_22 + a_rhs.m_z * m_32;
				value.m_w = a_rhs.m_w * m_03 + a_rhs.m_w * m_13 + a_rhs.m_w * m_23 + a_rhs.m_w * m_33;

				return value;
			}

			inline Mat4& Rotation(Vec3 a_rotation)
			{
				Mat4 newRotMat = Mat4::Identity();
				
				newRotMat.RotateX(a_rotation.m_x);
				newRotMat.RotateY(a_rotation.m_y);
				newRotMat.RotateZ(a_rotation.m_z);

				m_00 = newRotMat.m_00;
				m_01 = newRotMat.m_01;
				m_02 = newRotMat.m_02;

				m_10 = newRotMat.m_10;
				m_11 = newRotMat.m_11;
				m_12 = newRotMat.m_12;

				m_20 = newRotMat.m_20;
				m_21 = newRotMat.m_21;
				m_22 = newRotMat.m_22;

				return *this;
			} 
			
			inline Vec3 GetEuler()
			{
				Vec3 euler = Vec3(0,0,0);
				
				//Calc Euler

				return euler;
			}

			inline Vec3 GetPosition()
			{
				return Vec3(m_03, m_13, m_23);
			}
			inline Mat4& SetPosition(Vec3 a_position)
			{
				m_03 = a_position.m_x;
				m_13 = a_position.m_y;
				m_23 = a_position.m_z;

				return *this;
			}

			inline Mat4 Translate(Vec3& a_translation)
			{
				m_mat[0][3] += a_translation.m_x;
				m_mat[1][3] += a_translation.m_y;
				m_mat[2][3] += a_translation.m_z;

				return *this;
			}

			inline Vec3 GetScale()
			{
				Vec3 scale = Vec3(m_00,m_11,m_22);

				return scale;
			}

			inline Mat4& SetScale(float a_scale)
			{
				//Calc Scale    
				m_00 *= a_scale;
				m_11 *= a_scale;
				m_22 *= a_scale;

				return *this;
			}
			inline Mat4& SetScale(Vec3 a_scale)
			{
				//Calc Scale    
				m_00 = a_scale.m_x;
				m_11 = a_scale.m_y;
				m_22 = a_scale.m_z;

				return *this;
			}

            inline Math::Vec3 GetRight()
            {
                Math::Vec3 right;
                
                right.m_x = m_00;
                right.m_y = m_01;
                right.m_z = m_02;

                return right.Normalize();
            }    

            inline Math::Vec3 GetUp()
            {
                Math::Vec3 up;
                
                up.m_x = m_10;
                up.m_y = m_11;
                up.m_z = m_12;

                return up.Normalize();
            }

            inline Math::Vec3 GetForward()
            {
                Math::Vec3 forward;
                
                forward.m_x = m_20;
                forward.m_y = m_21;
                forward.m_z = m_22;

                return forward.Normalize();
            }  

			

		private:
			inline void RotateX(float a_radians)
			{
				const float c = cos(a_radians);
				const float s = sin(a_radians);
				Mat4 rot = Mat4::Identity();
				
				rot.m_11 = c; rot.m_21 = -s;
				rot.m_12 = s; rot.m_22 = c;

				*this = rot * *this;
			}	
			inline void RotateY(float a_radians)
			{
				const float c = cos(a_radians);
				const float s = sin(a_radians);
				Mat4 rot = Mat4::Identity();
				
				rot.m_00 = c;  rot.m_20 = s;
				rot.m_02 = -s; rot.m_22 = c;				

				*this = rot * *this;
			}	
			inline void RotateZ(float a_radians)
			{
				const float c = cos(a_radians);
				const float s = sin(a_radians);
				Mat4 rot = Mat4::Identity();
				
				rot.m_00 = c; rot.m_10 = -s;
				rot.m_01 = s; rot.m_11 = c;

				*this = rot * *this;
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

	// === Helpers
		inline float Distance(Vec2 a_rhs, Vec2 a_lhs)
		{
			float x = a_lhs.m_x - a_rhs.m_x;
			float y = a_lhs.m_y - a_rhs.m_y;

			return abs(sqrtf(x * x + y * y));
		}
		inline float Distance(Vec3 a_rhs, Vec3 a_lhs)
		{
			float x = a_lhs.m_x - a_rhs.m_x;
			float y = a_lhs.m_y - a_rhs.m_y;
			float z = a_lhs.m_z - a_rhs.m_z;
			
			return abs(sqrtf(x * x + y * y + z *z));
		}

		inline float MoveTowards(float a_rhs, float a_lhs, float a_delta)
		{
			float lenght = a_lhs - a_rhs;

			if(lenght < 0.05f && lenght > -0.05f)
			{
				return a_lhs;
			}

			if(lenght > 0)
			{
				return (a_rhs + a_delta);
			}
			else 
			{
				return (a_rhs - a_delta);
			}
		}

		inline Vec2 Direction(Vec2 a_origin, Vec2 a_destination)
		{
			return a_destination - a_origin;
		}
		inline Vec3 Direction(Vec3 a_origin, Vec3 a_destination)
		{
			return a_destination - a_origin;
		}

		inline Vec2 Lerp(Vec2 a_rhs, Vec2 a_lhs, float a_delta)
		{
			float x = (1 - a_delta) * a_rhs.m_x + a_delta * a_lhs.m_x;
			float y = (1 - a_delta) * a_rhs.m_y + a_delta * a_lhs.m_y;
			
			return Math::Vec2(x,y);
		}
		inline Vec3 Lerp(Vec3 a_rhs, Vec3 a_lhs, float a_delta)
		{
			float x = (1 - a_delta) * a_rhs.m_x + a_delta * a_lhs.m_x;
			float y = (1 - a_delta) * a_rhs.m_y + a_delta * a_lhs.m_y;
			float z = (1 - a_delta) * a_rhs.m_z + a_delta * a_lhs.m_z;
			
			return Math::Vec3(x,y,z);
		}

		inline Vec2 MoveTowards(Vec2 a_rhs, Vec2 a_lhs, float a_delta)
		{
			Math::Vec2 returnValue;

			returnValue.m_x = MoveTowards(a_rhs.m_x, a_lhs.m_x, a_delta);
			returnValue.m_y = MoveTowards(a_rhs.m_y, a_lhs.m_y, a_delta);

			return returnValue;
		}
		inline Vec3 MoveTowards(Vec3 a_rhs, Vec3 a_lhs, float a_delta)
		{
			Math::Vec3 returnValue;

			returnValue.m_x = MoveTowards(a_rhs.m_x, a_lhs.m_x, a_delta);
			returnValue.m_y = MoveTowards(a_rhs.m_y, a_lhs.m_y, a_delta);
			returnValue.m_z = MoveTowards(a_rhs.m_z, a_lhs.m_z, a_delta);

			return returnValue;
		}

		inline Mat4 GetOrthographicMatrix(const float a_bottom, const float a_top, const float a_left, const float a_right, const float a_near, const float a_far)
		{
			Mat4 ortho = Mat4::Identity();

			float width = 1.0f / (a_right - a_left);
			float height = 1.0f / (a_top - a_bottom);
			float fRange = 1.0f / (a_far - a_near);

			ortho.m_mat[0][0] = width + width;
			ortho.m_mat[0][3] = -(a_left + a_right) * width;

			ortho.m_mat[1][1] = height + height;
			ortho.m_mat[1][3] = -(a_top + a_bottom) * height;

			ortho.m_mat[2][2] = fRange;
			ortho.m_mat[2][3] = -fRange * a_near;

			ortho.m_mat[3][3] = 1.0f;

			return ortho;
		}
		inline Mat4 GetProjectionMatrix(const float a_angleOfView, const float a_aspect, const float a_near, const float a_far)
		{
			Mat4 projection = Mat4::Identity();
			
			float rad = GETRADIUS(a_angleOfView);
			float tanHalfFOV = std::tan(rad * 0.5f);

			projection.m_mat[0][0] = 1 / (a_aspect * tanHalfFOV);
			projection.m_mat[1][1] = 1 / (tanHalfFOV);

			projection.m_mat[2][2] = (a_far + a_near) / (a_far - a_near);
			projection.m_mat[2][3] = (2 * a_far * a_near) / (a_far - a_near);

			projection.m_mat[3][2] = 1;

			return projection;
		}

		inline Mat4 Transpose(const Mat4 a_matrix)
		{
			Mat4 transposed = a_matrix;

			std::swap(transposed.m_m[1], transposed.m_m[4]);
			std::swap(transposed.m_m[2], transposed.m_m[8]);
			std::swap(transposed.m_m[3], transposed.m_m[12]);
			std::swap(transposed.m_m[6], transposed.m_m[9]);
			std::swap(transposed.m_m[7], transposed.m_m[13]);
			std::swap(transposed.m_m[11], transposed.m_m[14]);

			return transposed;
		}

	}
}