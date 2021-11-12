#include "MePCH.h"
#include "Platform/General/Editor/EditorStats.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Graphics/RenderLayer.h"

Me::Editor::EditorStats::EditorStats(Renderer::RenderLayer& a_renderLayer)
	:
	m_renderLayer(&a_renderLayer)
{
	m_open = false;
	m_frames = 0;
}

Me::Editor::EditorStats::~EditorStats()
{

}

void Me::Editor::EditorStats::Update(float a_dt)
{
	m_frames++;
	if (m_frames % 30 == 0)
	{
		m_deltaTime = a_dt * 1000;
	}
}

void Me::Editor::EditorStats::Draw()
{
	ImGui::Begin("Stats");
	Renderer::RenderStats stats = m_renderLayer->GetRenderStats();
	std::string delta = "ms : " + std::to_string(m_deltaTime);
	ImGui::LabelText("##ms", delta.c_str());
	std::string drawCalls = "DrawCalls : " + std::to_string(stats.m_drawCalls);
	ImGui::LabelText("##DrawCalls", drawCalls.c_str());
	std::string vertices = "Vertices : " + std::to_string(stats.m_vertices);
	ImGui::LabelText("##Vertices", vertices.c_str());

	ImGui::End();
}