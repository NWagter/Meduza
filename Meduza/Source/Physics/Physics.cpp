#include "MePCH.h"
#include "Physics/Physics.h"

#include "Utils/MeduzaDebug.h"

Me::Math::Vector3 Me::Physics::PhysicsHelper::GetFurthestPointInDirection
(
	Math::Matrix4 const& a_transform, 
	Me::Math::Vector3 const& a_direction, 
	std::vector<HullVertex> const& a_points, 
	Math::Vector3 const a_scale,	
	Math::Vector3 const a_offset
)
{
	float distance = std::numeric_limits<float>::lowest();
	Math::Vector3 const searchDirection = (Math::SetInverseRotation(a_transform.GetEuler()) * a_direction).Normalize();
	Math::Vector3 point;
	Math::Matrix4 rotation = Math::RotationMatrix(a_transform.GetEuler());

	for (size_t i = 0; i < a_points.size(); i++)
	{
		if (Me::Debug::MeduzaDebug::GetDebuggingSettings().m_showVertices)
		{
			Math::Vector3 point = a_points[i].m_point;
			Math::Vector3 const rotatedPoint = (a_transform.GetPosition() + a_offset) + (rotation * (point * a_scale));
			Math::Matrix4 trans = Math::CreateTransformationMatrix(rotatedPoint, Math::Vector3(0.0f), Math::Vector3(1.0f));
			Me::Debug::MeduzaDebug::RenderCircle(trans, Me::Debug::MeduzaDebug::GetDebuggingSettings().m_scaleVertices, a_points[i].m_debugColour);
		}

		float d = Me::Math::DotProduct(searchDirection, a_points[i].m_point);
		if (d > distance)
		{
			distance = d;
			point = a_points[i].m_point;
		}
	}

	Math::Vector3 rotatedPoint = rotation * (point * a_scale);
	return (a_transform.GetPosition() + a_offset) + rotatedPoint;
}