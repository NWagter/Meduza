#include "MePCH.h"
#include "Physics/GJKAlgorithm.h"

#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/PhysicsComponent.h"

const size_t gc_maxInterations = 5;

bool Me::Physics::GJKAlgorithm::GJKIntersaction(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Physics::CollisionData& a_data)
{
	Math::Vector3 direction = Math::Direction(a_physics[0]->m_transform.GetPosition(), a_physics[1]->m_transform.GetPosition()).Normalize();

	if (direction.Lenght() == 0)
	{
		return true;
	}

	Simplex simplex;

	Math::Vector3 pointA = Support(a_physics, a_colliders, direction);
	simplex.AddPoint(pointA);

	direction = Inverse(pointA);

	for (size_t i = 0; i < gc_maxInterations; i++)
	{
		Math::Vector3 nextPoint = Support(a_physics, a_colliders, direction);

		if (DotProduct(nextPoint, direction) < 0)
		{
			return false;
		}

		simplex.AddPoint(nextPoint);

		if (simplex.HandleSimplex(direction))
		{
			a_data.m_otherPosition = a_physics[1]->m_transform.GetPosition();
			
			// This is not Correct! TODO : I will need to look into getting the HitNormal and HitPosition!
			a_data.m_hitNormal = (a_physics[0]->m_transform.GetPosition() - a_physics[1]->m_transform.GetPosition()).Normalize();
			return true;
		}
	}

	return false;
}

Me::Math::Vector3 Me::Physics::GJKAlgorithm::Support(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Math::Vector3 const a_direction)
{
	Math::Vector3 furthersPointA = a_colliders[0]->GetFurthestPointInDirection(a_physics[0]->m_transform, a_direction);
	Math::Vector3 furthersPointB = a_colliders[1]->GetFurthestPointInDirection(a_physics[1]->m_transform, Inverse(a_direction));

	// TODO : Need to consider the transformation of a shape can be gotten from the body
	return furthersPointA - furthersPointB;
}

bool Me::Physics::Simplex::AddPoint(Math::Vector3 const& a_point)
{
	if (m_amountOfPoints < 4)
	{
		m_points[m_amountOfPoints] = a_point;
		++m_amountOfPoints;
		return true;
	}

	return false;
}

bool Me::Physics::Simplex::HandleSimplex(Math::Vector3& a_direction)
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

bool Me::Physics::Simplex::SameDirection(Math::Vector3 const& a_direction, Math::Vector3 const& a_ao)
{
	return DotProduct(a_direction, a_ao) > 0.0f;
}

bool Me::Physics::Simplex::Line(Math::Vector3& a_direction)
{
	Math::Vector3 a = m_points[0];
	Math::Vector3 b = m_points[1];

	Math::Vector3 ab = b - a;
	Math::Vector3 ao = Inverse(a);

	if (SameDirection(ab, ao))
	{
		a_direction = Math::CrossProduct(Math::CrossProduct(ab, ao), ab);
	}
	else
	{
		a_direction = ao;
	}

	return false;
}

bool Me::Physics::Simplex::Triangle(Math::Vector3& a_direction)
{
	Math::Vector3 a = m_points[0];
	Math::Vector3 b = m_points[1];
	Math::Vector3 c = m_points[2];

	Math::Vector3 ab = b - a;
	Math::Vector3 ac = c - a;
	Math::Vector3 ao = Inverse(a);

	Math::Vector3 abc = CrossProduct(ab, ac);

	if (SameDirection(a_direction, ao))
	{
		if (SameDirection(ac, ao))
		{
			a_direction = Math::CrossProduct(Math::CrossProduct(ac, ao), ac);
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

bool Me::Physics::Simplex::Tetrahedron(Math::Vector3& a_direction)
{
	Math::Vector3 a = m_points[0];
	Math::Vector3 b = m_points[1];
	Math::Vector3 c = m_points[2];
	Math::Vector3 d = m_points[3];

	Math::Vector3 ab = b - a;
	Math::Vector3 ac = c - a;
	Math::Vector3 ad = d - a;
	Math::Vector3 ao = Inverse(a);

	Math::Vector3 abc = CrossProduct(ab, ac);
	Math::Vector3 acd = CrossProduct(ac, ad);
	Math::Vector3 adb = CrossProduct(ad, ab);

	if (SameDirection(abc, ao))
	{
		return Triangle(a_direction);
	}
	if (SameDirection(acd, ao))
	{
		m_points[1] = c;
		m_points[2] = d;

		return Triangle(a_direction);
	}
	if (SameDirection(adb, ao))
	{
		m_points[1] = d;
		m_points[2] = b;

		return Triangle(a_direction);
	}

	return true;
}