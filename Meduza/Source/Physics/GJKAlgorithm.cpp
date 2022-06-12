#include "MePCH.h"
#include "Physics/GJKAlgorithm.h"

#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/PhysicsComponent.h"

#include "Utils/MeduzaDebug.h"

const size_t gc_maxInterations = 5;

bool Me::Physics::Simplex::AddPoint(Math::Vector3 const& a_point)
{
	if (m_amountOfPoints < 4)
	{
		m_points.push_back(a_point);
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

void Me::Physics::Simplex::Splice(uint16_t const a_index, uint16_t a_indexToRemove, Math::Vector3 const a_point)
{
	std::vector<Math::Vector3> newList;
	uint16_t counter = 0;

	for (size_t i = 0; i < Length(); i++)
	{
		if (i == a_index)
		{
			newList.push_back(a_point);
		}

		if (i > a_index && counter > 0)
		{
			counter--;
			continue;
		}

		newList.push_back(m_points.at(i));
	}

	m_amountOfPoints = newList.size();
	m_points = newList;
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

bool Me::Physics::GJKAlgorithm::GJKIntersaction(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Physics::CollisionData& a_data)
{
	if (a_colliders[0]->Is3DCollider() != a_colliders[1]->Is3DCollider())
	{
		return false;
	}

	Math::Vector3 direction = Math::Direction(a_physics[0]->m_transform.GetPosition(), a_physics[1]->m_transform.GetPosition());

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
			Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement);
			Math::Vector3 sHalfSize = a_colliders[0]->GetColliderScale() / 2.0f;

			if (!a_colliders[0]->Is3DCollider())
			{
				EPAData data = EPA2D(simplex, a_physics, a_colliders);
				a_data.m_hitNormal = data.m_normal;
				a_data.m_hitPoint = sPos - (sHalfSize * data.m_normal);
			}
			else
			{
				//TODO : THIS IS NOT CORRECT!
				a_data.m_hitNormal = (a_physics[0]->m_transform.GetPosition() - a_physics[1]->m_transform.GetPosition()).Normalize();
				a_data.m_hitPoint = sPos - (sHalfSize * a_data.m_hitNormal);
			}

			if (Me::Debug::MeduzaDebug::GetDebuggingSettings().m_drawHitPoints)
			{
				Me::Debug::MeduzaDebug::RenderCircle(Math::CreateTransformationMatrix(a_data.m_hitPoint, Math::Vector3(0.0f), Math::Vector3(1.0f)),
					Me::Debug::MeduzaDebug::GetDebuggingSettings().m_scaleVertices,
					Colours::BLACK);
			}

			return true;
		}
	}

	return false;
}

Me::Math::Vector3 Me::Physics::GJKAlgorithm::Support(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Math::Vector3 const a_direction)
{
	Math::Vector3 furthersPointA = a_colliders[0]->GetFurthestPointInDirection(a_physics[0]->m_transform, a_direction);
	Math::Vector3 furthersPointB = a_colliders[1]->GetFurthestPointInDirection(a_physics[1]->m_transform, Inverse(a_direction));


	if (Me::Debug::MeduzaDebug::GetDebuggingSettings().m_gjkDebugger)
	{
		Me::Debug::MeduzaDebug::RenderLine(furthersPointA, furthersPointA + a_direction, Colours::RED);
		Me::Debug::MeduzaDebug::RenderLine(furthersPointB, furthersPointB + Inverse(a_direction), Colours::WHITE);
	}

	return (furthersPointA - furthersPointB).Normalize();
}

Me::Physics::EPAData Me::Physics::GJKAlgorithm::EPA2D(Simplex const a_simplex, Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2])
{
	EPAData data;
	float const infinity = std::numeric_limits<float>::infinity();
	uint16_t minIndex = 0;
	data.m_distance = infinity;

	uint8_t maxItter = 5;

	Simplex polytope = a_simplex;
	while (data.m_distance == infinity && maxItter > 0)
	{
		for (size_t i = 0; i < polytope.Length(); i++)
		{
			size_t j = (i + 1) % polytope.Length();
			Math::Vector3 vertexI = polytope.GetPoint(i);
			Math::Vector3 vertexJ = polytope.GetPoint(j);

			Math::Vector3 vertexIJ = vertexJ - vertexI;
			Math::Vector3 normal = Math::Vector3(vertexIJ.m_y, -vertexIJ.m_x, 0.0f).Normalize();
			float distance = Math::DotProduct(normal, vertexI);

			if (distance < 0)
			{
				distance *= -1.0f;
				normal.Inverse();
			}

			if (distance < data.m_distance)
			{
				data.m_distance = distance;
				data.m_normal = normal;
				minIndex = j;
			}
		}
	
		Math::Vector3 support = Support(a_physics, a_colliders, data.m_normal);
		float sDistance = Math::DotProduct(data.m_normal, support);

		if (std::abs(sDistance - data.m_distance) > 0.001f)
		{
			data.m_distance = infinity;
			polytope.Splice(minIndex, 0, support);
			maxItter--;
		}
	}

	return data;
}