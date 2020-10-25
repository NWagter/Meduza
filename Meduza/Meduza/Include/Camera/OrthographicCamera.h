#pragma once

#include "Camera.h"

namespace meduza
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(math::Vec4, math::Vec2 = math::Vec2(-1,1));
		~OrthographicCamera() override;

		inline void SetEye(math::Vec3 a_pos) override { m_position = glm::vec3(a_pos.m_x, a_pos.m_y, a_pos.m_z); RecalculateViewMatrix(); }
		inline void SetRotation(math::Vec3 a_euler) override { m_rotationZ = a_euler.m_z; RecalculateViewMatrix();}

		inline void SetColour(Colour a_colour) override { m_solidColour = a_colour; };
		inline Colour GetSolidColour() const override { return m_solidColour; };

		inline math::Vec3 GetEyePos() const override { return math::Vec3(m_position.x, m_position.y, m_position.z); }
		inline math::Vec3 GetRotation() const override { return math::Vec3(0, 0, m_rotationZ); };

		void SetProjection(math::Vec2, math::Vec2 = math::Vec2(-1, 1)) override;

		CameraPerspective GetActive() const override { return CameraPerspective::Orthographic; }

		const glm::mat4& GetprojectionMatrix() const override { return m_projectionMatrix; }
		const glm::mat4& GetViewMatrix() const override { return m_viewMatrix; }
		const glm::mat4& GetViewProjection() const override { return m_viewProjection; }

	private:
		void RecalculateViewMatrix();

		glm::mat4 m_projectionMatrix = glm::mat4(1);
		glm::mat4 m_viewMatrix = glm::mat4(1);
		glm::mat4 m_viewProjection = glm::mat4(1);
		
		glm::vec3 m_position = glm::vec3(0);
		float m_rotationZ = 0;

		Colour m_solidColour = Colours::CELESTIAL_BLUE;


	};
}