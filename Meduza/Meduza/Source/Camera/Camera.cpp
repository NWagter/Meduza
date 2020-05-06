#include "mePch.h"

#include "Camera/Camera.h"

#include "Camera/OrthographicCamera.h"

meduza::Camera* meduza::Camera::CreateCamera(CameraPerspective a_perspective, math::Vec4 a_frustrum, math::Vec2 a_distance)
{
	switch (a_perspective)
	{
	case meduza::CameraPerspective::Orthographic:
		return new OrthographicCamera(a_frustrum, a_distance);
		break;
	case meduza::CameraPerspective::Perspective:
		return nullptr;
		break;
	}

	return nullptr;
}
