#pragma once

namespace Me
{
	namespace Physics
	{
		struct ColliderComponent;
		struct CollisionData;
		struct PhysicsComponent;
	}

	namespace Collision
	{
		class GJKAlgorithm
		{
		public:
			static bool GJKIntersaction(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Physics::CollisionData& a_data);
		private:
			static Math::Vector3 Support(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Math::Vector3 const a_direction);
		};

		class Simplex
		{
		public:
			bool AddPoint(Math::Vector3 const& a_point);
			bool HandleSimplex(Math::Vector3& a_direction);

		private:
			bool SameDirection(Math::Vector3 const& a_direction, Math::Vector3 const& a_ao);

			bool Line(Math::Vector3& a_direction);
			bool Triangle(Math::Vector3& a_direction);
			bool Tetrahedron(Math::Vector3& a_direction);

			Math::Vector3 m_points[4];
			int m_amountOfPoints = 0;
		};
	}
}