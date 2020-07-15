#pragma once

#include "Platform/General/Resources/Mesh.h"

#include <glad/glad.h>

namespace meduza
{
	class MeshGL : public Mesh
	{
	public:
		MeshGL(unsigned int, std::vector<Vertex>, std::vector<int>, VertexAttributes, GLenum = GL_LINE);
		~MeshGL() override;

		void EnableMode();
		void GenerateBuffers();
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