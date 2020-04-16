#include "mePch.h"

#include "Gfx/OpenGL/RendererOpenGL.h"

meduza::renderer::RendererOpenGL::RendererOpenGL(Window&)
{
	printf("Create OpenGL Renderer \n");
}

meduza::renderer::RendererOpenGL::~RendererOpenGL()
{
	printf("Delete OpenGL Renderer \n");
}

void meduza::renderer::RendererOpenGL::Clear(Colour)
{
}

void meduza::renderer::RendererOpenGL::Draw(Sprite)
{
}

void meduza::renderer::RendererOpenGL::Draw(Mesh)
{
}

void meduza::renderer::RendererOpenGL::Draw(Text)
{
}

void meduza::renderer::RendererOpenGL::Render()
{
}
