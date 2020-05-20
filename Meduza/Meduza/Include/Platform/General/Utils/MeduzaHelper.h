#pragma once

#include "Util/MeduzaUtil.h"

namespace meduza
{
	static const int  GS_FRAMEBUFFERS = 3;

	namespace renderer
	{
		class Mesh;
	}

	class MeduzaHelper
	{
	public:
		static API ms_activeAPI;
		static bool ms_imGui;
		static bool ms_minimized;
	};

	struct DrawData
	{
		DrawData()
		{
			m_position = glm::vec3(0);
			m_size = glm::vec3(1);
			m_rotation = glm::vec3(0);
			m_textCoords = glm::vec4(0, 0, 1, 1);
			m_colour = glm::vec4(1, 1, 1, 1);
			m_shaderId = 0;
			m_textureId = 0;

		}

		~DrawData() = default;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_size;
		glm::vec4 m_textCoords;

		glm::vec4 m_colour;

		renderer::Mesh* m_mesh;

		unsigned int m_shaderId;
		unsigned int m_textureId;
	};

	struct Vertex
	{
		Vertex(float a_x, float a_y, float a_z)
		{
			m_vertexPos = glm::vec3(a_x, a_y, a_z);
		}

		glm::vec3 m_vertexPos;
	};

	namespace utils
	{
		inline static unsigned int GetHashedID(std::string a_strToHash)
		{
			return unsigned int(std::hash<std::string>{}(a_strToHash));
		}
	}
}