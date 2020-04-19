#include "mePch.h"

#include "Core/Drawable/Drawable.h"

#include "Gfx/Core/Renderer.h"

meduza::drawable::Drawable::~Drawable()
{

}

void meduza::drawable::Drawable::Submit(renderer::Renderer& a_renderer)
{
	a_renderer.Submit(this);
}
