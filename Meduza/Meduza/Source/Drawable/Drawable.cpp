#include "mePch.h"

#include "Platform/General/Utils/MeduzaHelper.h"

#include "Drawable/Drawable.h"
#include "Platform/General/Gfx/Renderer.h"

void meduza::drawable::Drawable::Submit(renderer::Renderer& a_renderer)
{
	if (!MeduzaHelper::ms_minimized && m_drawData->m_material != nullptr)
	{
		a_renderer.Draw(this);
		return;
	}
}
