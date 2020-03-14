#include "cepch.h"
#include "Gfx/Drawables/Sprite.h"

#include "Gfx/Camera.h"
#include "Gfx/RenderLayer.h"

namespace ce
{
	Sprite::Sprite()
	{
		m_drawData.m_drawtype = cr::DrawType::Quad;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Draw(cr::RenderLayer& a_renderLayer)
	{
		//Model.
		glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale, 1));

		glm::quat q = glm::quat(m_rotation);
		glm::mat4 r = glm::toMat4(q);

		glm::mat4 p = glm::translate(glm::mat4(1.0f), glm::vec3(m_position, 1));

		m_drawData.m_model = s * r * p;

		//ViewProjection.
		glm::mat4 vp = glm::mat4();
		Camera* c = ce::Camera::GetMainCamera();
		if (c != nullptr)
		{
			vp = c->GetViewProjectionMatrix();
		}

		m_drawData.m_viewProjection = vp;

		//Color.
		m_drawData.m_color = m_color;

		a_renderLayer.Draw(this);
	}
}
