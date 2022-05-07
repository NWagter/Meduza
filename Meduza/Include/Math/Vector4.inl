namespace Me
{
	namespace Math
	{
		inline bool operator==(Vector4 a_rhs, Vector4 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z || a_rhs.m_w != a_lhs.m_w)
			{
				return false;
			}

			return true;
		}
		inline bool operator!=(Vector4 a_rhs, Vector4 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z || a_rhs.m_w != a_lhs.m_w)
			{
				return true;
			}

			return false;
		}
	}
}