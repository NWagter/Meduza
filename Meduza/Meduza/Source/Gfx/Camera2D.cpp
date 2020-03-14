#include "cepch.h"
#include "Gfx/Camera2D.h"

namespace ce
{
	void Camera2D::SetBounds(const glm::vec2& a_bounds)
	{
		m_bounds = a_bounds;

		m_dirtyProjection = true;
	}

	void Camera2D::SetRenderDistance(const glm::vec2& a_z)
	{
		m_z = a_z;

		m_dirtyProjection = true;
	}

	void Camera2D::SetOrthographicProjection(const glm::vec2& a_size)
	{
		m_size = a_size;

		m_dirtyProjection = true;
	}

	void Camera2D::LookAt(const glm::vec3& a_target, const glm::vec3& a_up)
	{
#pragma warning(push)
#pragma warning(disable : 4127)
		m_viewMatrix = glm::lookAt(m_position, a_target, a_up);
#pragma warning(pop)
		m_rotation = glm::toQuat(m_viewMatrix);
	}

	void Camera2D::LookDir(const glm::vec3& a_dir, const glm::vec3& a_up)
	{
//#pragma warning(push)
//#pragma warning(disable : 4127)
//		m_viewMatrix = glm::lookAt(m_position, m_position + a_dir, a_up);
//#pragma warning(pop)
		m_rotation = glm::quatLookAt(a_dir, a_up);
		//m_rotation = glm::toQuat(m_viewMatrix);

		m_dirtyView = true;
	}

	glm::mat4 Camera2D::GetProjectionMatrix()
	{
		if (m_dirtyProjection)
		{
			m_dirtyProjection = false;
			UpdateProjectionMatrix();
		}

		return m_projectionMatrix;
	}

	glm::mat4 Camera2D::GetInverseProjectionMatrix()
	{
		if (m_dirtyProjection)
		{
			m_dirtyProjection = false;
			UpdateProjectionMatrix();
		}

		return m_inverseProjectionMatrix;
	}

	glm::mat4 Camera2D::GetViewMatrix()
	{
		if (m_dirtyView)
		{
			m_dirtyView = false;
			UpdateViewMatrix();
		}

		return m_viewMatrix;
	}

	glm::mat4 Camera2D::GetInverseViewMatrix()
	{
		if (m_dirtyView)
		{
			m_dirtyView = false;
			UpdateViewMatrix();
		}

		return m_inverseViewMatrix;
	}

	void Camera2D::UpdateProjectionMatrix()
	{
		m_dirtyViewProjection = true;

		float viewWidth;
		float viewHeight;
		float orthographicSize;
		
		float aspectRatio = m_size.x / m_size.y;
		float targetAspectRatio = m_bounds.x / m_bounds.y;

		if (targetAspectRatio < aspectRatio)
		{
			orthographicSize = m_bounds.y / 2.f;
		}
		else
		{
			float dif = targetAspectRatio / aspectRatio;
			orthographicSize = m_bounds.y / 2.f * dif;
		}

		viewHeight =/* 2.f **/ orthographicSize;
		viewWidth = viewHeight * aspectRatio;

		m_projectionMatrix = glm::ortho(-viewWidth, viewWidth, viewHeight, -viewHeight, m_z.x, m_z.y);
		m_inverseProjectionMatrix = glm::inverse(m_projectionMatrix);
	}

	void Camera2D::UpdateViewMatrix()
	{
		m_dirtyViewProjection = true;

		glm::vec3 pos = m_position;
		glm::mat4 trans = GetTranslationMatrix();
		m_viewMatrix = GetTranslationMatrix() * GetRotationMatrix();
		m_inverseViewMatrix = glm::inverse(m_viewMatrix);
	}
}