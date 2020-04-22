#include "mePch.h"

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/General/Window.h"

meduza::renderer::RendererGL::RendererGL()
{
}

meduza::renderer::RendererGL::~RendererGL()
{

}

void meduza::renderer::RendererGL::Clear(Colour)
{
}

void meduza::renderer::RendererGL::SwapBuffers()
{
	Renderer::GetWindow().SwapBuffers();
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable*)
{
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*>)
{
}
