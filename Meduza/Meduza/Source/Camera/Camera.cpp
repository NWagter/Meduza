#include "mePch.h"

#include "Camera/Camera.h"

#include "Camera/OrthographicCamera.h"

meduza::Camera* meduza::Camera::CreateCamera(CameraPerspective a_perspective, math::Vec2 a_size, math::Vec2 a_distance)
{
	switch (a_perspective)
	{
	case meduza::CameraPerspective::Orthographic:
	{
		math::Vec4 frustrum(-a_size.m_x / 2, a_size.m_x / 2, -a_size.m_y / 2, a_size.m_y / 2);
		return new OrthographicCamera(frustrum, a_distance);
		break;
	}
	case meduza::CameraPerspective::Perspective:
	{
		return nullptr;
		break;
	}
	}

	return nullptr;
}
