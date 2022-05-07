#pragma once

namespace Me
{
	namespace Math
	{
		class Matrix4
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

				float m_m[4 * 4];
			};
#pragma warning(pop)
		public:
			Matrix4(
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

			Matrix4(float a_matrix[16])
			{
				for (int i = 0; i < 16; i++)
				{
					m_m[i] = a_matrix[i];
				}
			}

			Matrix4()
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

			static inline Matrix4 Identity()
			{
				return Matrix4(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
			}
			inline Matrix4& Inverse()
			{
				Matrix4 temp = *this;

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

				for (int i = 0; i < 16; i++)
				{
					m_m[i] = temp.m_m[i];
				}

				return *this;
			}

			inline Matrix4& operator=(Matrix4 a_rhs)
			{
				for (int i = 0; i < 16; i++)
					m_m[i] = a_rhs.m_m[i];

				return *this;
			}
			inline Matrix4 operator+(const Matrix4& a_rhs)
			{
				Matrix4 temp = *this;

				for (int i = 0; i < 16; i++)
				{
					temp.m_m[i] += a_rhs.m_m[i];
				}

				return temp;
			}
			inline Matrix4 operator*(const Matrix4& a_rhs)
			{
				Matrix4 result = Matrix4::Identity();
				Matrix4 self = *this;

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

			inline Vector4 operator*(const Vector4& a_rhs)
			{
				Vector4 value;

				value.m_x = a_rhs.m_x * m_00 + a_rhs.m_x * m_10 + a_rhs.m_x * m_20 + a_rhs.m_x * m_30;
				value.m_y = a_rhs.m_y * m_01 + a_rhs.m_y * m_11 + a_rhs.m_y * m_21 + a_rhs.m_y * m_31;
				value.m_z = a_rhs.m_z * m_02 + a_rhs.m_z * m_12 + a_rhs.m_z * m_22 + a_rhs.m_z * m_32;
				value.m_w = a_rhs.m_w * m_03 + a_rhs.m_w * m_13 + a_rhs.m_w * m_23 + a_rhs.m_w * m_33;

				return value;
			}
			inline Vector3 operator*(const Vector3& a_rhs)
			{
				Vector4 result = Matrix4(m_m) * Vector4(a_rhs, 1.0f);
				return Vector3(result.m_x / result.m_w, result.m_y / result.m_w, result.m_z / result.m_w);
			}

			inline Matrix4& operator*=(const Matrix4& a_rhs)
			{
				*this = *this * a_rhs;
				return *this;
			}

			inline Matrix4& Rotation(Vector3 a_rotation)
			{
				Matrix4 newRotMat = Matrix4::Identity();

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
			inline void SetInverseRotation(Vector3 const& a_euler)
			{
				Matrix4 newRotMat = Matrix4::Identity();
				newRotMat.RotateZ(-a_euler.m_z);
				newRotMat.RotateY(-a_euler.m_y);
				newRotMat.RotateX(-a_euler.m_x);

				m_00 = newRotMat.m_00;
				m_01 = newRotMat.m_01;
				m_02 = newRotMat.m_02;

				m_10 = newRotMat.m_10;
				m_11 = newRotMat.m_11;
				m_12 = newRotMat.m_12;

				m_20 = newRotMat.m_20;
				m_21 = newRotMat.m_21;
				m_22 = newRotMat.m_22;
			}
			inline Vector3 GetEuler()
			{
				Vector3 euler = Vector3(0, 0, 0);

				//Calc Euler

				return euler;
			}

			inline Vector3 GetPosition()
			{
				return Vector3(m_03, m_13, m_23);
			}
			inline Matrix4& SetPosition(Vector3 a_position)
			{
				m_03 = a_position.m_x;
				m_13 = a_position.m_y;
				m_23 = a_position.m_z;

				return *this;
			}
			inline Matrix4 Translate(Vector3& a_translation)
			{
				m_mat[0][3] += a_translation.m_x;
				m_mat[1][3] += a_translation.m_y;
				m_mat[2][3] += a_translation.m_z;

				return *this;
			}

			inline Vector3 GetScale()
			{
				Vector3 scale = Vector3(m_00, m_11, m_22);

				return scale;
			}
			inline Matrix4& SetScale(float a_scale)
			{
				//Calc Scale    
				m_00 *= a_scale;
				m_11 *= a_scale;
				m_22 *= a_scale;

				return *this;
			}
			inline Matrix4& SetScale(Vector3 a_scale)
			{
				//Calc Scale    
				m_00 = a_scale.m_x;
				m_11 = a_scale.m_y;
				m_22 = a_scale.m_z;

				return *this;
			}

			inline Vector3 GetRight()
			{
				Vector3 right;

				right.m_x = m_00;
				right.m_y = m_01;
				right.m_z = m_02;

				return right.Normalize();
			}
			inline Vector3 GetUp()
			{
				Vector3 up;

				up.m_x = m_10;
				up.m_y = m_11;
				up.m_z = m_12;

				return up.Normalize();
			}
			inline Vector3 GetForward()
			{
				Vector3 forward;

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
				Matrix4 rot = Matrix4::Identity();

				rot.m_11 = c; rot.m_21 = -s;
				rot.m_12 = s; rot.m_22 = c;

				*this = rot * *this;
			}
			inline void RotateY(float a_radians)
			{
				const float c = cos(a_radians);
				const float s = sin(a_radians);
				Matrix4 rot = Matrix4::Identity();

				rot.m_00 = c;  rot.m_20 = s;
				rot.m_02 = -s; rot.m_22 = c;

				*this = rot * *this;
			}
			inline void RotateZ(float a_radians)
			{
				const float c = cos(a_radians);
				const float s = sin(a_radians);
				Matrix4 rot = Matrix4::Identity();

				rot.m_00 = c; rot.m_10 = -s;
				rot.m_01 = s; rot.m_11 = c;

				*this = rot * *this;
			}

		};

		inline Matrix4 GetOrthographicMatrix(const float a_bottom, const float a_top, const float a_left, const float a_right, const float a_near, const float a_far);
		inline Matrix4 GetProjectionMatrix(const float a_angleOfView, const float a_aspect, const float a_near, const float a_far);

		inline Matrix4 Transpose(Matrix4 const& a_matrix);

		inline Matrix4 SetInverseRotation(Matrix4 const& a_matrix, Vector3 const& a_euler);

	}
}

#include "Math/Matrix4.inl"