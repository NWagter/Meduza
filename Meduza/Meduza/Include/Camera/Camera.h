#pragma once

#include "Util/MeduzaUtil.h"
#include "Math/MeduzaMath.h"

namespace meduza
{
	class Camera
	{
	public:
		static Camera* CreateCamera(CameraPerspective, math::Vec2, math::Vec2);

		virtual ~Camera() = default;

		virtual void SetEye(math::Vec3) = 0;
		virtual void SetRotation(math::Vec3) = 0;
		virtual math::Vec3 GetEyePos() const = 0;
		virtual math::Vec3 GetRotation() const = 0;
		virtual void SetColour(Colour) = 0;
		virtual Colour GetSolidColour() const = 0;

		virtual void SetProjection(math::Vec2, math::Vec2 = math::Vec2(-1, 1)) = 0;

		virtual CameraPerspective GetActive() const = 0;

		virtual const glm::mat4& GetprojectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjection() const = 0;
	};
}