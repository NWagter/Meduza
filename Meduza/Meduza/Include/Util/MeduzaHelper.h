#pragma once

#include "MeduzaUtil.h"

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
		static bool ms_optick;
		static bool ms_imGui;

	};

	struct DrawData
	{
		DrawData()
		{
			m_position = glm::vec3(0);
			m_size = glm::vec3(1);
			m_rotation = glm::vec3(0);

			m_materialId = 0;
		}

		~DrawData() = default;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_size;

		renderer::Mesh* m_mesh;

		unsigned int m_materialId;
	};

	struct Vertex
	{
		Vertex(float a_x, float a_y, float a_z)
		{
			m_vertexPos = glm::vec3(a_x, a_y, a_z);
			m_textureCoord = glm::vec2(0);
			m_normals = glm::vec2(0);
		}
		Vertex(float a_x, float a_y, float a_z, float a_u, float a_v)
		{
			m_vertexPos = glm::vec3(a_x, a_y, a_z);
			m_textureCoord = glm::vec2(a_u, a_v);
			m_normals = glm::vec2(0);
		}
		Vertex(float a_x, float a_y, float a_z, float a_u, float a_v, float a_nX, float a_nY)
		{
			m_vertexPos = glm::vec3(a_x, a_y, a_z);
			m_textureCoord = glm::vec2(a_u, a_v);
			m_normals = glm::vec2(a_nX, a_nY);
		}

		void SetVertex(float a_x, float a_y, float a_z)
		{
			m_vertexPos = glm::vec3(a_x, a_y, a_z);
		}
		void SetUV(float a_u, float a_v)
		{
			m_textureCoord = glm::vec2(a_u, a_v);
		}
		void SetNormals(float a_x, float a_y)
		{
			m_normals = glm::vec2(a_x, a_y);
		}

		glm::vec3 m_vertexPos;
		glm::vec2 m_textureCoord;
		glm::vec2 m_normals;
	};


}