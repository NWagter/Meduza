#pragma once
#include "Gfx/IDrawable.h"
#include "glm/glm.hpp"

namespace cr { class RenderLayer; }

namespace ce
{
	class Sprite : 
		public cr::IDrawable
	{
	public:
		Sprite();
		virtual ~Sprite();

		void Draw(cr::RenderLayer& a_renderLayer) override;

		glm::vec2 m_position = glm::vec2(0, 0);
		glm::vec2 m_scale = glm::vec2(1, 1);
		glm::vec3 m_rotation = glm::vec3(0, 0, 0);
		glm::vec4 m_color = glm::vec4(1, 0, 1, 1);

	protected:
		
	private:
	};
}