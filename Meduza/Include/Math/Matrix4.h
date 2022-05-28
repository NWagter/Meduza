#pragma once
#include "Core/Core.h"

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

				//Calculate matrix
				{
					temp.m_m[0] = m_m[5] * m_m[10] * m_m[15] -
						m_m[5] * m_m[11] * m_m[14] -
						m_m[9] * m_m[6] * m_m[15] +
						m_m[9] * m_m[7] * m_m[14] +
						m_m[13] * m_m[6] * m_m[11] -
						m_m[13] * m_m[7] * m_m[10];

					temp.m_m[4] = -m_m[4] * m_m[10] * m_m[15] +
						m_m[4] * m_m[11] * m_m[14] +
						m_m[8] * m_m[6] * m_m[15] -
						m_m[8] * m_m[7] * m_m[14] -
						m_m[12] * m_m[6] * m_m[11] +
						m_m[12] * m_m[7] * m_m[10];

					temp.m_m[8] = m_m[4] * m_m[9] * m_m[15] -
						m_m[4] * m_m[11] * m_m[13] -
						m_m[8] * m_m[5] * m_m[15] +
						m_m[8] * m_m[7] * m_m[13] +
						m_m[12] * m_m[5] * m_m[11] -
						m_m[12] * m_m[7] * m_m[9];

					temp.m_m[12] = -m_m[4] * m_m[9] * m_m[14] +
						m_m[4] * m_m[10] * m_m[13] +
						m_m[8] * m_m[5] * m_m[14] -
						m_m[8] * m_m[6] * m_m[13] -
						m_m[12] * m_m[5] * m_m[10] +
						m_m[12] * m_m[6] * m_m[9];

					temp.m_m[1] = -m_m[1] * m_m[10] * m_m[15] +
						m_m[1] * m_m[11] * m_m[14] +
						m_m[9] * m_m[2] * m_m[15] -
						m_m[9] * m_m[3] * m_m[14] -
						m_m[13] * m_m[2] * m_m[11] +
						m_m[13] * m_m[3] * m_m[10];

					temp.m_m[5] = m_m[0] * m_m[10] * m_m[15] -
						m_m[0] * m_m[11] * m_m[14] -
						m_m[8] * m_m[2] * m_m[15] +
						m_m[8] * m_m[3] * m_m[14] +
						m_m[12] * m_m[2] * m_m[11] -
						m_m[12] * m_m[3] * m_m[10];

					temp.m_m[9] = -m_m[0] * m_m[9] * m_m[15] +
						m_m[0] * m_m[11] * m_m[13] +
						m_m[8] * m_m[1] * m_m[15] -
						m_m[8] * m_m[3] * m_m[13] -
						m_m[12] * m_m[1] * m_m[11] +
						m_m[12] * m_m[3] * m_m[9];

					temp.m_m[13] = m_m[0] * m_m[9] * m_m[14] -
						m_m[0] * m_m[10] * m_m[13] -
						m_m[8] * m_m[1] * m_m[14] +
						m_m[8] * m_m[2] * m_m[13] +
						m_m[12] * m_m[1] * m_m[10] -
						m_m[12] * m_m[2] * m_m[9];

					temp.m_m[2] = m_m[1] * m_m[6] * m_m[15] -
						m_m[1] * m_m[7] * m_m[14] -
						m_m[5] * m_m[2] * m_m[15] +
						m_m[5] * m_m[3] * m_m[14] +
						m_m[13] * m_m[2] * m_m[7] -
						m_m[13] * m_m[3] * m_m[6];

					temp.m_m[6] = -m_m[0] * m_m[6] * m_m[15] +
						m_m[0] * m_m[7] * m_m[14] +
						m_m[4] * m_m[2] * m_m[15] -
						m_m[4] * m_m[3] * m_m[14] -
						m_m[12] * m_m[2] * m_m[7] +
						m_m[12] * m_m[3] * m_m[6];

					temp.m_m[10] = m_m[0] * m_m[5] * m_m[15] -
						m_m[0] * m_m[7] * m_m[13] -
						m_m[4] * m_m[1] * m_m[15] +
						m_m[4] * m_m[3] * m_m[13] +
						m_m[12] * m_m[1] * m_m[7] -
						m_m[12] * m_m[3] * m_m[5];

					temp.m_m[14] = -m_m[0] * m_m[5] * m_m[14] +
						m_m[0] * m_m[6] * m_m[13] +
						m_m[4] * m_m[1] * m_m[14] -
						m_m[4] * m_m[2] * m_m[13] -
						m_m[12] * m_m[1] * m_m[6] +
						m_m[12] * m_m[2] * m_m[5];

					temp.m_m[3] = -m_m[1] * m_m[6] * m_m[11] +
						m_m[1] * m_m[7] * m_m[10] +
						m_m[5] * m_m[2] * m_m[11] -
						m_m[5] * m_m[3] * m_m[10] -
						m_m[9] * m_m[2] * m_m[7] +
						m_m[9] * m_m[3] * m_m[6];

					temp.m_m[7] = m_m[0] * m_m[6] * m_m[11] -
						m_m[0] * m_m[7] * m_m[10] -
						m_m[4] * m_m[2] * m_m[11] +
						m_m[4] * m_m[3] * m_m[10] +
						m_m[8] * m_m[2] * m_m[7] -
						m_m[8] * m_m[3] * m_m[6];

					temp.m_m[11] = -m_m[0] * m_m[5] * m_m[11] +
						m_m[0] * m_m[7] * m_m[9] +
						m_m[4] * m_m[1] * m_m[11] -
						m_m[4] * m_m[3] * m_m[9] -
						m_m[8] * m_m[1] * m_m[7] +
						m_m[8] * m_m[3] * m_m[5];

					temp.m_m[15] = m_m[0] * m_m[5] * m_m[10] -
						m_m[0] * m_m[6] * m_m[9] -
						m_m[4] * m_m[1] * m_m[10] +
						m_m[4] * m_m[2] * m_m[9] +
						m_m[8] * m_m[1] * m_m[6] -
						m_m[8] * m_m[2] * m_m[5];
				}

				float det = m_m[0] * temp.m_m[0] + m_m[1] * temp.m_m[4] + m_m[2] * temp.m_m[8] + m_m[3] * temp.m_m[12];

				if (det == 0)
				{
					ME_CORE_ASSERT_M(true, "Invalid Inverse");
					return *this;
				}

				det = 1.0f / det;

				for (int i = 0; i < 16; i++)
					m_m[i] = temp.m_m[i] * det;

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

				for (auto i = 0; i < 4; ++i)
				{
					for (auto j = 0; j < 4; ++j)
					{
						value[i] += m_mat[i][j] * a_rhs[j];
					}
				}

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

				newRotMat.RotateX(GETRADIAN(a_rotation.m_x));
				newRotMat.RotateY(GETRADIAN(a_rotation.m_y));
				newRotMat.RotateZ(GETRADIAN(a_rotation.m_z));

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
				newRotMat.RotateZ(GETRADIAN(-a_euler.m_z));
				newRotMat.RotateY(GETRADIAN(-a_euler.m_y));
				newRotMat.RotateX(GETRADIAN(-a_euler.m_x));
				
				m_m[0] = newRotMat.m_m[0];
				m_m[1] = newRotMat.m_m[1];
				m_m[2] = newRotMat.m_m[2];
				m_m[4] = newRotMat.m_m[4];
				m_m[5] = newRotMat.m_m[5];
				m_m[6] = newRotMat.m_m[6];
				m_m[8] = newRotMat.m_m[8];
				m_m[9] = newRotMat.m_m[9];
				m_m[10] = newRotMat.m_m[10];
			}
			inline Vector3 GetEuler() const
			{
				float sy = std::sqrt(m_mat[0][0] * m_mat[0][0] + m_mat[1][0] * m_mat[1][0]);

				bool singular = sy < 1e-6;

				float x, y, z;
				if (!singular)
				{
					x = std::atan2(m_mat[2][1], m_mat[2][2]);
					y = std::atan2(-m_mat[2][0], sy);
					z = std::atan2(m_mat[1][0], m_mat[0][0]);
				}
				else
				{
					x = std::atan2(-m_mat[1][2], m_mat[1][1]);
					y = std::atan2(-m_mat[2][0], sy);
					z = 0;
				}

				return Vector3(GETDEGREE(x), GETDEGREE(y), GETDEGREE(z));
			}
			inline Matrix4 GetRotationMatrix() const
			{
				Matrix4 temp = Matrix4::Identity();
				temp.Rotation(GetEuler());

				return temp;
			}

			inline Vector3 GetPosition() const
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
			inline Matrix4 GetTranslationMatrix() const
			{
				Matrix4 temp = Matrix4::Identity();
				temp.SetPosition(GetPosition());

				return temp;
			}

			inline Vector3 GetScale() const
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
			inline Matrix4 GetScaleMatrix() const
			{
				Matrix4 temp = Matrix4::Identity();
				temp.GetScale();

				return temp;
			}

			inline Vector3 GetRight() const
			{
				Vector3 right;

				right.m_x = m_00;
				right.m_y = m_01;
				right.m_z = m_02;

				return right.Normalize();
			}
			inline Vector3 GetUp() const
			{
				Vector3 up;

				up.m_x = m_10;
				up.m_y = m_11;
				up.m_z = m_12;

				return up.Normalize();
			}
			inline Vector3 GetForward() const
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
				const float c = std::cos(a_radians);
				const float s = std::sin(a_radians);
				Matrix4 rot = Matrix4::Identity();

				rot.m_mat[1][1] = c; rot.m_mat[1][2] = -s;
				rot.m_mat[2][1] = s; rot.m_mat[2][2] = c;

				*this = rot * *this;
			}
			inline void RotateY(float a_radians)
			{
				const float c = std::cos(a_radians);
				const float s = std::sin(a_radians);
				Matrix4 rot = Matrix4::Identity();

				rot.m_mat[0][0] = c;  rot.m_mat[0][2] = s;
				rot.m_mat[2][0] = -s; rot.m_mat[2][2] = c;

				*this = rot * *this;
			}
			inline void RotateZ(float a_radians)
			{
				const float c = std::cos(a_radians);
				const float s = std::sin(a_radians);
				Matrix4 rot = Matrix4::Identity();

				rot.m_mat[0][0] = c; rot.m_mat[0][1] = -s;
				rot.m_mat[1][0] = s; rot.m_mat[1][1] = c;

				*this = rot * *this;
			}

		};

		inline Matrix4 TranslationMatrix(Vector3 const& a_position, Matrix4 a_matrix = Matrix4::Identity());
		inline Matrix4 ScaleMatrix(Vector3 const& a_scale, Matrix4 a_matrix = Matrix4::Identity());
		inline Matrix4 RotationMatrix(Vector3 const& a_euler, Matrix4 a_matrix = Matrix4::Identity());

		inline Matrix4 GetOrthographicMatrix(const float a_bottom, const float a_top, const float a_left, const float a_right, const float a_near, const float a_far);
		inline Matrix4 GetProjectionMatrix(const float a_angleOfView, const float a_aspect, const float a_near, const float a_far);
		inline Matrix4 CreateLookAtMatrix(Vector3 const& a_eye, Vector3 const& a_target, Vector3 const& a_up);

		inline Matrix4 Transpose(Matrix4 const& a_matrix);

		inline Matrix4 SetInverseRotation(Vector3 const& a_euler, Matrix4 const& a_matrix = Matrix4::Identity());
		inline Matrix4 CreateTransformationMatrix(Vector3 const& a_postion, Vector3 const& a_euler, Vector3 const& a_scale);

	}
}

#include "Math/Matrix4.inl"