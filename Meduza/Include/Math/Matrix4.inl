namespace Me
{
	namespace Math
	{
		inline Matrix4 TranslationMatrix(Vector3 const& a_position, Matrix4 a_matrix)
		{
			a_matrix.SetPosition(a_position);
			return a_matrix;
		}
		inline Matrix4 ScaleMatrix(Vector3 const& a_scale, Matrix4 a_matrix)
		{
			a_matrix.SetScale(a_scale);
			return a_matrix;
		}
		inline Matrix4 RotationMatrix(Vector3 const& a_euler, Matrix4 a_matrix)
		{
			a_matrix.Rotation(a_euler);
			return a_matrix;
		}

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

			float rad = GETRADIAN(a_angleOfView);
			float tanHalfFOV = std::tan(rad * 0.5f);

			projection.m_mat[0][0] = 1 / (a_aspect * tanHalfFOV);
			projection.m_mat[1][1] = 1 / (tanHalfFOV);

			projection.m_mat[2][2] = (a_far + a_near) / (a_far - a_near);
			projection.m_mat[2][3] = (2 * a_far * a_near) / (a_far - a_near);

			projection.m_mat[3][2] = 1;

			return projection;
		}
		inline Matrix4 CreateLookAtMatrix(Vector3 const& a_eye, Vector3 const& a_target, Vector3 const& a_up)
		{
			Vector3 n = Direction(a_target, a_eye).Normalize();
			n.Normalize();

			Vector3 u = CrossProduct(a_up, n);
			u.Normalize();
			//
			Vector3 v = CrossProduct(n, u);

			Matrix4 lookat(u[0], v[0], n[0], 0.0f,
				u[1], v[1], n[1], 0.0f,
				u[2], v[2], n[2], 0.0f,
				DotProduct(u.Inverse(), a_eye),
				DotProduct(v.Inverse(), a_eye),
				DotProduct(n.Inverse(), a_eye),
				1.0f);

			return lookat;
		}

		inline Matrix4 Transpose(Matrix4 const& a_matrix)
		{
			Matrix4 transposed = a_matrix;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < i; j++)
					std::swap(transposed.m_mat[i][j], transposed.m_mat[j][i]);

			return transposed;
		}

		inline Matrix4 SetInverseRotation(Vector3 const& a_euler, Matrix4 const& a_matrix)
		{
			Matrix4 result = a_matrix;
			result.SetInverseRotation(a_euler);

			return result;
		}

		inline Matrix4 CreateTransformationMatrix(Vector3 const& a_postion, Vector3 const& a_euler, Vector3 const& a_scale)
		{
			Matrix4 translation = TranslationMatrix(a_postion) * RotationMatrix(a_euler) * ScaleMatrix(a_scale);
			return translation;
		}
	}
}