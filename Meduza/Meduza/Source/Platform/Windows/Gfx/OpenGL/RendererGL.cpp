#include "mePch.h"

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/General/Window.h"

#include <glad/glad.h>

meduza::renderer::RendererGL::RendererGL()
{
	int status = gladLoadGL(); 
	assertm(status, "Glad not loaded");

	std::string version = (char*)(glGetString(GL_VERSION));
	printf("OpenGl version : %s \n", version.c_str());

	glViewport(0, 0, int(Renderer::GetWindow().GetSize().m_x), int(Renderer::GetWindow().GetSize().m_y));
}

meduza::renderer::RendererGL::~RendererGL()
{
	delete Renderer::m_window;
}

void meduza::renderer::RendererGL::Clear(Colour a_colour)
{
#if OPTICK
	OPTICK_GPU_EVENT("Clear");
#endif

	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b, a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererGL::SwapBuffers()
{
	PopulateBuffers();

	Renderer::GetWindow().SwapBuffers();
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable*)
{
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*>)
{
}

void meduza::renderer::RendererGL::PreRender()
{
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
	PreRender();
#if OPTICK
	OPTICK_GPU_EVENT("Render Frame");
#endif // 
}
