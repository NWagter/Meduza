#include "MePCH.h"
#include "Utils/MeduzaDebug.h"

#include "Platform/General/Graphics/RenderLayer.h"

Me::Debug::MeduzaDebug* Me::Debug::MeduzaDebug::ms_instance = nullptr;

Me::Debug::MeduzaDebug* Me::Debug::MeduzaDebug::CreateDebugger(Renderer::RenderLayer& a_renderer)
{
	if (ms_instance != nullptr)
	{
		ME_ASSERT_M(true, "Can't have multiple debuggers!");
	}

	ms_instance = new MeduzaDebug(a_renderer);
	return ms_instance;
}

Me::Debug::MeduzaDebug::MeduzaDebug(Renderer::RenderLayer& a_renderer)
{
	m_renderLayer = &a_renderer;
}

Me::Debug::MeduzaDebug::~MeduzaDebug()
{
	ms_instance = nullptr;
}

void Me::Debug::MeduzaDebug::RenderLine(Math::Vec3 a_start, Math::Vec3 a_end, Colour a_colour)
{
#ifndef EDITOR
	return;
#endif // !EDITOR


	Renderer::LineRender line;
	line.m_start = a_start;
	line.m_end = a_end;
	line.m_colour = a_colour;
	ms_instance->m_renderLayer->RenderLine(line);
}

void Me::Debug::MeduzaDebug::RenderLine( Math::Vec3 a_start, Math::Vec3 a_direction, float a_lenght, Colour a_colour)
{
#ifndef EDITOR
	return;
#endif // !EDITOR
	Renderer::LineRender line;
	line.m_start = a_start;
	line.m_end = a_start + (a_direction * a_lenght);
	line.m_colour = a_colour;
	ms_instance->m_renderLayer->RenderLine(line);
}