#pragma once

#define GETRADIAN(a_degree) (a_degree * 3.141592654f / 180)
#define GETDEGREE(a_radian) (a_radian * (180 / 3.141592654f))

namespace Me
{
	namespace Math
	{
		static constexpr float gs_pi = 3.141592654f;
		static constexpr float gs_pi2 = 6.283185307f;

	// === Helpers
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

		namespace Random
		{
			static constexpr float gs_seed = 12121998;
			inline float RandomRange(const float a_min, const float a_max)
			{
				float max = std::max(a_min, a_max);
				float min = std::min(a_min, a_max);

				float randomDelta = ((float)rand()) / (float)RAND_MAX;
				float r = (1 - randomDelta) * min + randomDelta * max;
				return r;
			}
		}
	}
}

#include <cmath>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"