#include "mePch.h"

#include "Platform/Windows/Utils/OpenGL/HelperGL.h"

#include <Glad/glad.h>

unsigned int meduza::renderer::helper::HelperGL::CreateEmptyVbo(int a_size, void* a_adress)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, a_size * sizeof(float), a_adress, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}
