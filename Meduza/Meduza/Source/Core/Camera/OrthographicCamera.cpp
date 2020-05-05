#include "mePch.h"

#include "Camera/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

meduza::OrthographicCamera::OrthographicCamera(math::Vec4 a_frustrum, math::Vec2 a_distance)
{
	m_projectionMatrix = glm::ortho(a_frustrum.m_x, a_frustrum.m_y, a_frustrum.m_z, a_frustrum.m_w, a_distance.m_x, a_distance.m_y);
	m_viewMatrix = glm::mat4(1);
	m_viewProjection = m_projectionMatrix * m_viewMatrix;
}

meduza::OrthographicCamera::~OrthographicCamera()
{
}

void meduza::OrthographicCamera::SetProjection(math::Vec4 a_frustrum, math::Vec2 a_distance)
{
	m_projectionMatrix = m_projectionMatrix = glm::ortho(a_frustrum.m_x, a_frustrum.m_y, a_frustrum.m_z, a_frustrum.m_w, a_distance.m_x, a_distance.m_y);
}

void meduza::OrthographicCamera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * 
		glm::rotate(glm::mat4(1), m_rotationZ, glm::vec3(0,0,1));

	m_viewMatrix = glm::inverse(transform);

	m_viewProjection = m_projectionMatrix * m_viewMatrix;
}
