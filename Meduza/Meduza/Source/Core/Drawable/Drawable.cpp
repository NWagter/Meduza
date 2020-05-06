#include "mePch.h"

#include "Util/MeduzaHelper.h"

#include "Core/Drawable/Drawable.h"
#include "Platform/General/Gfx/Renderer.h"

void meduza::drawable::Drawable::Submit(renderer::Renderer& a_renderer)
{
	if (!MeduzaHelper::ms_minimized)
	{
		a_renderer.Draw(this);
		return;
	}
}
