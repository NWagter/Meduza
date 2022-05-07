namespace Me
{
	namespace Math
	{
		inline Matrix4 GetOrthographicMatrix(const float a_bottom, const float a_top, const float a_left, const float a_right, const float a_near, const float a_far)
		{
			Matrix4 ortho = Matrix4::Identity();

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
		inline Matrix4 GetProjectionMatrix(const float a_angleOfView, const float a_aspect, const float a_near, const float a_far)
		{
			Matrix4 projection = Matrix4::Identity();

			float rad = GETRADIUS(a_angleOfView);
			float tanHalfFOV = std::tan(rad * 0.5f);

			projection.m_mat[0][0] = 1 / (a_aspect * tanHalfFOV);
			projection.m_mat[1][1] = 1 / (tanHalfFOV);

			projection.m_mat[2][2] = (a_far + a_near) / (a_far - a_near);
			projection.m_mat[2][3] = (2 * a_far * a_near) / (a_far - a_near);

			projection.m_mat[3][2] = 1;

			return projection;
		}

		inline Matrix4 Transpose(Matrix4 const& a_matrix)
		{
			Matrix4 transposed = a_matrix;

			std::swap(transposed.m_m[1], transposed.m_m[4]);
			std::swap(transposed.m_m[2], transposed.m_m[8]);
			std::swap(transposed.m_m[3], transposed.m_m[12]);
			std::swap(transposed.m_m[6], transposed.m_m[9]);
			std::swap(transposed.m_m[7], transposed.m_m[13]);
			std::swap(transposed.m_m[11], transposed.m_m[14]);

			return transposed;
		}

		inline Matrix4 SetInverseRotation(Matrix4 const& a_matrix, Vector3 const& a_euler)
		{
			Matrix4 result = a_matrix;
			result.SetInverseRotation(a_euler);

			return result;
		}
	}
}