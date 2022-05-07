namespace Me
{
	namespace Math
	{
		inline bool operator==(Vector3 a_rhs, Vector3 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z)
			{
				return false;
			}

			return true;
		}
		inline bool operator!=(Vector3 a_rhs, Vector3 a_lhs)
		{
			if (a_rhs.m_x != a_lhs.m_x || a_rhs.m_y != a_lhs.m_y || a_rhs.m_z != a_lhs.m_z)
			{
				return true;
			}

			return false;
		}

		inline float Distance(Vector3 a_rhs, Vector3 a_lhs)
		{
			float x = a_lhs.m_x - a_rhs.m_x;
			float y = a_lhs.m_y - a_rhs.m_y;
			float z = a_lhs.m_z - a_rhs.m_z;

			return abs(sqrtf(x * x + y * y + z * z));
		}
		inline Vector3 Direction(Vector3 a_origin, Vector3 a_destination)
		{
			return a_destination - a_origin;
		}

		inline Vector3 Lerp(Vector3 a_rhs, Vector3 a_lhs, float a_delta)
		{
			float x = (1 - a_delta) * a_rhs.m_x + a_delta * a_lhs.m_x;
			float y = (1 - a_delta) * a_rhs.m_y + a_delta * a_lhs.m_y;
			float z = (1 - a_delta) * a_rhs.m_z + a_delta * a_lhs.m_z;

			return Math::Vector3(x, y, z);
		}
		inline Vector3 MoveTowards(Vector3 a_rhs, Vector3 a_lhs, float a_delta)
		{
			Math::Vector3 returnValue;

			returnValue.m_x = MoveTowards(a_rhs.m_x, a_lhs.m_x, a_delta);
			returnValue.m_y = MoveTowards(a_rhs.m_y, a_lhs.m_y, a_delta);
			returnValue.m_z = MoveTowards(a_rhs.m_z, a_lhs.m_z, a_delta);

			return returnValue;
		}

		inline Vector3 LookAtRotation(Vector3 a_target, Vector3 a_origin)
		{
			Vector3 angles = Vector3(0);
			// Axis in the game, need to know it to fix up:
			//              : L - R  ; F - B ;  U - D
			// Rotation Axis:   x        z        y
			// Translation  :   y        x        z

			Vector3 dir = a_target - a_origin;
			Vector3 temp = dir * Math::Distance(a_target, a_origin);

			angles.m_x = GETRADIUS(temp.m_y);
			angles.m_y = GETRADIUS(temp.m_x);

			return angles;
		}

		inline float DotProduct(Vector3 const& a_rhs, Vector3 const& a_lhs)
		{
			float const x = a_rhs.m_x * a_lhs.m_x;
			float const y = a_rhs.m_y * a_lhs.m_y;
			float const z = a_rhs.m_z * a_lhs.m_z;

			float const dotProduct = x + y + z;

			return dotProduct;
		}
		inline Vector3 CrossProduct(Vector3 const& a_rhs, Vector3 const& a_lhs)
		{
			float const cX = (a_rhs.m_y * a_lhs.m_z) - (a_rhs.m_z * a_lhs.m_y);
			float const cY = (a_rhs.m_z * a_lhs.m_x) - (a_rhs.m_x * a_lhs.m_z);
			float const cZ = (a_rhs.m_x * a_lhs.m_y) - (a_rhs.m_y * a_lhs.m_x);

			Vector3 const crossProduct(cX, cY, cZ);

			return crossProduct;
		}
		inline Vector3 TrippleCrossProduct(Vector3 const& a_vecA, Vector3 const& a_vecB, Vector3 const& a_vecC)
		{
			// == A X (b X C)
			return CrossProduct(a_vecA, CrossProduct(a_vecB, a_vecC));
		}

		inline Vector3 Inverse(Vector3 const& a_rhs)
		{
			return Math::Vector3(-a_rhs.m_x, -a_rhs.m_y, -a_rhs.m_z);
		}

		namespace Random
		{
			inline Vector3 RandomRange(const Vector3 a_min, const Vector3 a_max)
			{
				Vector3 result;

				result.m_x = RandomRange(a_min.m_x, a_max.m_x);
				result.m_y = RandomRange(a_min.m_y, a_max.m_y);
				result.m_z = RandomRange(a_min.m_z, a_max.m_z);

				return result;
			}
		}
	}
}