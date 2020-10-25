#pragma once

#include "Platform/General/Resources/Mesh.h"

#include <glad/glad.h>

namespace meduza
{
	class MeshGL : public Mesh
	{
	public:
		MeshGL(unsigned int, std::vector<Vertex>, std::vector<uint16_t>, VertexAttributes, GLenum = GL_FILL);
		~MeshGL() override;

		void EnableMode();
		void GenerateBuffers() override;
		void GenerateAttributes();

		unsigned int GetVBO() const { return m_vbo; }
		unsigned int GetVAO() const { return m_vao; }
		unsigned int GetIBO() const { return m_ibo; }

	private:
		unsigned int m_vbo;
		unsigned int m_ibo;
		unsigned int m_vao;

		GLenum m_mode;

	};
}