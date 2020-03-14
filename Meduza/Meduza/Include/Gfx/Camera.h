#pragma once

namespace ce
{
	class Camera
	{
	public:
		Camera();
		virtual ~Camera();

		virtual glm::mat4 GetProjectionMatrix() = 0;
		virtual glm::mat4 GetInverseProjectionMatrix() = 0;
		virtual glm::mat4 GetViewMatrix() = 0;
		virtual glm::mat4 GetInverseViewMatrix() = 0;
		glm::mat4 GetViewProjectionMatrix();

		void SetPosition(const glm::vec3& a_position);
		const glm::vec3& GetPosition();
		void SetRotation(const glm::quat& a_rotation);
		const glm::quat& GetRotation();

		static Camera* GetMainCamera();

	protected:
		virtual void UpdateProjectionMatrix() = 0;
		virtual void UpdateViewMatrix() = 0;

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();

		bool m_dirtyView = true;
		bool m_dirtyProjection = true;
		bool m_dirtyViewProjection = true;

		glm::vec3 m_position;
		glm::quat m_rotation;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_inverseProjectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_inverseViewMatrix;
		glm::mat4 m_viewProjectionMatrix;

		static Camera* gs_mainCamera;
	};
}