#pragma once

namespace Me
{
	namespace Physics
	{
		struct ColliderComponent;
		struct CollisionData;
		struct PhysicsComponent;

		class Simplex
		{
		public:
			bool AddPoint(Math::Vector3 const& a_point);
			bool HandleSimplex(Math::Vector3& a_direction);

			void Splice(uint16_t const a_index, uint16_t a_indexToRemove, Math::Vector3 const a_point);

			size_t Length() const { return m_amountOfPoints; }
			Math::Vector3 GetPoint(size_t a_index) const { return m_points[a_index]; }

		private:
			bool SameDirection(Math::Vector3 const& a_direction, Math::Vector3 const& a_ao);

			bool Line(Math::Vector3& a_direction);
			bool Triangle(Math::Vector3& a_direction);
			bool Tetrahedron(Math::Vector3& a_direction);

			std::vector<Math::Vector3> m_points;
			int m_amountOfPoints = 0;
		};

		struct EPAData
		{
			Math::Vector3 m_normal = Math::Vector3(0.0f);
			float m_distance = 0.0f;
		};

		class GJKAlgorithm
		{
		public:
			static bool GJKIntersaction(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Physics::CollisionData& a_data);
		private:
			static Math::Vector3 Support(Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2], Math::Vector3 const a_direction);
			static EPAData EPA2D(Simplex const a_simplex, Physics::PhysicsComponent* a_physics[2], Physics::ColliderComponent* a_colliders[2]);
		};
	}
}