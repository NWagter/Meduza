#include "mePch.h"
#include "Editor/EditorStats.h"

#include "Platform/General/Gfx/Renderer.h"


meduza::editor::EditorStats::EditorStats(renderer::Renderer& a_renderer)
{
	m_renderer = &a_renderer;
}

meduza::editor::EditorStats::~EditorStats()
{
}

void meduza::editor::EditorStats::Update(const float a_dt)
{
	m_timer += a_dt;

	if (m_timer >= 0.2f)
	{
		m_deltaSecond = a_dt * 1000;
		m_timer = 0;
	}

	renderer::DrawStatistics stats = m_renderer->GetDrawStatistics();

	if (ImGui::Begin("Stats"))
	{
		ImGui::Text("ms : %.2f", m_deltaSecond);
		ImGui::Text("DrawCalls : %i", stats.m_drawCalls);
		ImGui::Text("Instances : %i", stats.m_instances);
		ImGui::Text("Drawables : %i", stats.m_drawables);
		ImGui::Text("Vertices : %i", stats.m_vertices);
		ImGui::End();
	}
}
