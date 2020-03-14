#pragma once
#include "Gfx/Camera.h"
#include <glm/glm.hpp>

namespace ce
{
	class Camera2D :
		public Camera
	{
	public:
		Camera2D() = default;
		virtual ~Camera2D() = default;

		//The bounds of what always needs to be on screen.
		//Usually a value aligned with the aspect ratio.
		void SetBounds(const glm::vec2& a_bounds);
		//Near and far render distance.
		void SetRenderDistance(const glm::vec2& a_z);
		//Usually the render or window size.
		void SetOrthographicProjection(const glm::vec2& a_size);
		//Look at a target from the current direction.
		void LookAt(const glm::vec3& a_target, const glm::vec3& a_up);
		//Look in a direction.
		void LookDir(const glm::vec3& a_dir, const glm::vec3& a_up);

		glm::mat4 GetProjectionMatrix() override;
		glm::mat4 GetInverseProjectionMatrix() override;
		glm::mat4 GetViewMatrix() override;
		glm::mat4 GetInverseViewMatrix() override;

	protected:
		void UpdateProjectionMatrix() override;
		void UpdateViewMatrix() override;

	private:
		//What to keep on screen.
		glm::vec2 m_bounds = glm::vec2(16, 9);
		//Current window/render size.
		glm::vec2 m_size = glm::vec2(1280, 720);
		//Near, far clipping plane Z.
		glm::vec2 m_z = glm::vec2(0.1f, 100.0f);
	};
}