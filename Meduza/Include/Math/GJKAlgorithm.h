#pragma once

namespace Me
{
	namespace Physics
	{
		struct ColliderComponent;
		struct CollisionData;
		struct PhysicsComponent;
	}

	namespace Math
	{
		class GJKAlgorithm
		{
		public:
			static bool GJKIntersaction(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Physics::CollisionData& a_data);
		private:
			static Math::Vec3 Support(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Math::Vec3 const a_direction);
		};

		class Simplex
		{
		public:
			bool AddPoint(Math::Vec3 const& a_point);
			bool HandleSimplex(Math::Vec3& a_direction);

		private:
			bool SameDirection(Math::Vec3 const& a_direction, Math::Vec3 const& a_ao);

			bool Line(Math::Vec3& a_direction);
			bool Triangle(Math::Vec3& a_direction);
			bool Tetrahedron(Math::Vec3& a_direction);

			Math::Vec3 m_points[4];
			int m_amountOfPoints = 0;
		};
	}
}