#include "mePch.h"

#include "Core/Drawable/Drawable.h"

#include "Gfx/Core/Renderer.h"

void meduza::drawable::Drawable::Submit(renderer::Renderer& a_renderer)
{
	a_renderer.Draw(this);
}
