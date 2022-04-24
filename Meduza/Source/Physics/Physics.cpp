#include "MePCH.h"
#include "Physics/Physics.h"

Me::Math::Vec3 Me::Physics::PhysicsHelper::GetFurthestPointInDirection(Me::Math::Vec3 const& a_direction, std::vector<Math::Vec3> const& a_points)
{
	float distance = std::numeric_limits<float>::lowest();
	size_t furthersPointIndexA = -1;
	for (size_t i = 0; i < a_points.size(); i++)
	{
		//GetFurthersPointInDirection
		float d = Me::Math::DotProduct(a_direction, a_points[i]);
		if (d > distance)
		{
			distance = d;
			furthersPointIndexA = i;
		}
	}

	if (furthersPointIndexA < a_points.size() && furthersPointIndexA >= 0)
	{
		return a_points[furthersPointIndexA];
	}

	return Math::Vec3(0);
}