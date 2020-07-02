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

void meduza::OrthographicCamera::SetProjection(math::Vec2 a_size, math::Vec2 a_distance)
{

	math::Vec4 frustrum(-a_size.m_x / 2, a_size.m_x / 2, -a_size.m_y / 2, a_size.m_y / 2);

	m_projectionMatrix = m_projectionMatrix = glm::ortho(frustrum.m_x, frustrum.m_y, frustrum.m_z, frustrum.m_w, a_distance.m_x, a_distance.m_y);
	RecalculateViewMatrix();
}

void meduza::OrthographicCamera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * 
		glm::rotate(glm::mat4(1), m_rotationZ, glm::vec3(0,0,1));

	m_viewMatrix = glm::inverse(transform);

	m_viewProjection = m_projectionMatrix * m_viewMatrix;
}