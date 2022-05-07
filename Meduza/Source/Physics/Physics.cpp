#include "MePCH.h"
#include "Physics/Physics.h"

#include "Utils/MeduzaDebug.h"

Me::Math::Vector3 Me::Physics::PhysicsHelper::GetFurthestPointInDirection(Math::Matrix4 const& a_transform, Me::Math::Vector3 const& a_direction, std::vector<Math::Vector3> const& a_points)
{
	float distance = std::numeric_limits<float>::lowest();
	Math::Vector3 const searchDirection = Math::SetInverseRotation(Math::Matrix4::Identity(), a_transform.GetEuler()) * a_direction;
	Math::Vector3 point;
	Math::Vector3 position = a_transform.GetPosition();
	Math::Vector3 scale = a_transform.GetScale();
	Math::Matrix4 rotation = Math::Matrix4::Identity();
	rotation.Rotation(a_transform.GetEuler());

	for (size_t i = 0; i < a_points.size(); i++)
	{
		if (Me::Debug::MeduzaDebug::GetDebuggingSettings().m_gjkDebugger)
		{
			Math::Vector3 newPoint = a_points[i];
			Math::Vector3 pos = (position + rotation * (newPoint * scale));
			Math::Vector3 pointB = pos;
			pointB += searchDirection;
			Me::Debug::MeduzaDebug::RenderLine(pos, pointB, Colours::RED);
		}

		float d = Me::Math::DotProduct(searchDirection, a_points[i]);
		if (d > distance)
		{
			distance = d;
			point = a_points[i];
		}
	}

	return position + rotation * (point * scale);
}