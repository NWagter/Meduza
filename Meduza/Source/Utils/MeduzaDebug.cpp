#include "MePCH.h"
#include "Utils/MeduzaDebug.h"

#include "Platform/General/Graphics/RenderLayer.h"

Me::Debug::MeduzaDebug* Me::Debug::MeduzaDebug::ms_instance = nullptr;

Me::Debug::MeduzaDebug* Me::Debug::MeduzaDebug::CreateDebugger(Renderer::RenderLayer& a_renderLayer)
{
	if (ms_instance != nullptr)
	{
		ME_ASSERT_M(true, "Can't have multiple debuggers!");
	}

	ms_instance = new MeduzaDebug(a_renderLayer);
	return ms_instance;
}

Me::Debug::MeduzaDebug::MeduzaDebug(Renderer::RenderLayer& a_renderLayer)
{
	m_renderLayer = &a_renderLayer;
}

Me::Debug::MeduzaDebug::~MeduzaDebug()
{
	ms_instance = nullptr;
}

void Me::Debug::MeduzaDebug::RenderLine(Math::Vector3 const& a_start, Math::Vector3 const& a_end, Colour const a_colour)
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

void Me::Debug::MeduzaDebug::RenderLine(Math::Vector3& a_start, Math::Vector3& a_direction, float const a_lenght, Colour const a_colour)
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

void Me::Debug::MeduzaDebug::RenderCircle(Math::Matrix4 const& a_trans, float const a_radius, Colour const a_colour)
{
#ifndef EDITOR
	return;
#endif // !EDITOR
	Renderer::CircleRender circle;
	circle.m_transform = a_trans;
	circle.m_radius = a_radius;
	circle.m_colour = a_colour;
	ms_instance->m_renderLayer->RenderCircle(circle);
}

