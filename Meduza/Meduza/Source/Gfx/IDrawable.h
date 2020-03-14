#pragma once
#include "GFXHelper.h"
#include <glm/glm.hpp>

namespace cr { class RenderLayer; }

namespace cr
{
	struct DrawData
	{
		DrawType m_drawtype = DrawType::Quad;
		glm::mat4 m_model;
		glm::mat4 m_viewProjection;
		glm::vec4 m_color = glm::vec4(1, 0, 1, 1);
	};

	class IDrawable
	{
	public:
		IDrawable() = default;
		virtual ~IDrawable() = default;

		virtual void Draw(RenderLayer&) = 0;

		DrawData m_drawData;
	};


}