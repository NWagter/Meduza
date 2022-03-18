#include "MePCH.h"
#include "Math/GJKAlgorithm.h"

#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/PhysicsComponent.h"

const size_t gc_maxInterations = 5;

bool Me::Math::GJKAlgorithm::GJKIntersaction(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Physics::CollisionData& a_data)
{
	Vec3 direction = Math::Direction(a_physics[0]->m_position, a_physics[1]->m_position).Normalize();

	if (direction.Lenght() == 0)
	{
		return true;
	}

	Simplex simplex;

	Math::Vec3 pointA = Support(a_physics, a_colliders, direction);
	simplex.AddPoint(pointA);

	direction = Inverse(pointA);

	for (size_t i = 0; i < gc_maxInterations; i++)
	{
		Math::Vec3 nextPoint = Support(a_physics, a_colliders, direction);

		if (DotProduct(nextPoint, direction) < 0)
		{
			return false;
		}

		simplex.AddPoint(nextPoint);

		if (simplex.HandleSimplex(direction))
		{
			a_data.m_otherPosition = a_physics[1]->m_position; 
			
			// This is not Correct! TODO : I will need to look into getting the HitNormal and HitPosition!
			a_data.m_hitNormal = (a_physics[0]->m_position - a_physics[1]->m_position).Normalize();
			return true;
		}
	}

	return false;
}

Me::Math::Vec3 Me::Math::GJKAlgorithm::Support(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Math::Vec3 const a_direction)
{
	Vec3 direction = SetInverseRotation(Mat4::Identity(), a_physics[0]->m_rotation) * a_direction;
	Math::Vec3 furthersPointA = a_colliders[0]->GetFurthestPointInDirection(direction);
	direction = SetInverseRotation(Mat4::Identity(), a_physics[1]->m_rotation) * Inverse(a_direction);
	Math::Vec3 furthersPointB = a_colliders[1]->GetFurthestPointInDirection(direction);

	// TODO : Need to consider the transformation of a shape can be gotten from the body

	Mat4 rotation;
	rotation.Identity();
	rotation.Rotation(a_physics[0]->m_rotation);
	Vec3 pointA = rotation * (a_physics[0]->m_position + furthersPointA);
	rotation.Identity();
	rotation.Rotation(a_physics[1]->m_rotation);
	Vec3 pointB = rotation * (a_physics[1]->m_position + furthersPointB);

	return pointA - pointB;
}

bool Me::Math::Simplex::AddPoint(Math::Vec3 const& a_point)
{
	if (m_amountOfPoints < 4)
	{
		m_points[m_amountOfPoints] = a_point;
		++m_amountOfPoints;
		return true;
	}

	return false;
}

bool Me::Math::Simplex::HandleSimplex(Math::Vec3& a_direction)
{
	switch (m_amountOfPoints)
	{
	case 2:
		return Line(a_direction);
	case 3:
		return Triangle(a_direction);
	case 4:
		return Tetrahedron(a_direction);
	}
    return false;
}

bool Me::Math::Simplex::SameDirection(Math::Vec3 const& a_direction, Math::Vec3 const& a_ao)
{
	return DotProduct(a_direction, a_ao) > 0.0f;
}

bool Me::Math::Simplex::Line(Math::Vec3& a_direction)
{
	Vec3 a = m_points[0];
	Vec3 b = m_points[1];

	Vec3 ab = b - a;
	Vec3 ao = Inverse(a);

	if (SameDirection(ab, ao))
	{
		a_direction = TrippleCrossProduct(ab, ao, ab);
	}
	else
	{
		a_direction = ao;
	}

	return false;
}

bool Me::Math::Simplex::Triangle(Math::Vec3& a_direction)
{
	Vec3 a = m_points[0];
	Vec3 b = m_points[1];
	Vec3 c = m_points[2];

	Vec3 ab = b - a;
	Vec3 ac = c - a;
	Vec3 ao = Inverse(a);

	Vec3 abc = CrossProduct(ab, ac);

	if (SameDirection(a_direction, ao))
	{
		if (SameDirection(ac, ao))
		{
			a_direction = TrippleCrossProduct(ac, ao, ac);
		}
		else
		{
			return Line(a_direction);
		}
	}
	else
	{
		if (SameDirection(CrossProduct(ab, abc), ao))
		{
			return Line(a_direction);
		}
		else
		{
			if (SameDirection(abc, ao))
			{
				a_direction = abc;
			}
			else
			{
				a_direction = Inverse(abc);
			}
		}
	}

	return false;
}

bool Me::Math::Simplex::Tetrahedron(Math::Vec3& a_direction)
{
	Vec3 a = m_points[0];
	Vec3 b = m_points[1];
	Vec3 c = m_points[2];
	Vec3 d = m_points[3];

	Vec3 ab = b - a;
	Vec3 ac = c - a;
	Vec3 ad = d - a;
	Vec3 ao = Inverse(a);

	Vec3 abc = CrossProduct(ab, ac);
	Vec3 acd = CrossProduct(ac, ad);
	Vec3 adb = CrossProduct(ad, ab);

	if (SameDirection(abc, ao))
	{
		return Triangle(a_direction);
	}
	if (SameDirection(acd, ao))
	{
		m_points[1] = c;
		m_points[2] = d;
		m_amountOfPoints--;

		return Triangle(a_direction);
	}
	if (SameDirection(adb, ao))
	{
		m_points[1] = d;
		m_points[2] = b;
		m_amountOfPoints--;

		return Triangle(a_direction);
	}

	return true;
}