#include "cepch.h"
#include "Gfx/Camera.h"

namespace ce
{
	static Camera* gs_camera = nullptr;

	Camera::Camera()
	{
		if (gs_camera == nullptr)
		{
			gs_camera = this;
		}
	}

	Camera::~Camera()
	{
		if (gs_camera == this)
		{
			gs_camera = nullptr;
		}
	}

	glm::mat4 Camera::GetViewProjectionMatrix()
	{
		if (m_dirtyViewProjection)
		{
			m_dirtyViewProjection = false;
			m_viewProjectionMatrix = GetViewMatrix() * GetProjectionMatrix();
		}

		return m_viewProjectionMatrix;
	}

	void Camera::SetPosition(const glm::vec3& a_position)
	{
		m_position = a_position;

		m_dirtyView = true;
	}

	const glm::vec3& Camera::GetPosition()
	{
		return m_position;
	}

	void Camera::SetRotation(const glm::quat& a_rotation)
	{
		m_rotation = a_rotation; 

		m_dirtyView = true;
	}

	const glm::quat& Camera::GetRotation()
	{
		return m_rotation;
	}

	Camera* Camera::GetMainCamera()
	{
		return gs_camera;
	}

	glm::mat4 Camera::GetTranslationMatrix()
	{
		return glm::translate(glm::mat4(1.0f), m_position);
	}

	glm::mat4 Camera::GetRotationMatrix()
	{
		return glm::toMat4(m_rotation);
	}
}