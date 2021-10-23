#include "MePCH.h"

#include "Platform/General/Editor/EditorRendererGL.h"
#include "Platform/General/Graphics/RenderLayerGL.h"

#include <imgui_impl_opengl3.h>

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include <imgui_impl_win32.h>
#elif PLATFORM_LINUX

#endif

#include "Platform/General/Editor/EditorToolbar.h"
#include "Platform/General/Editor/EditorEntityHierarchy.h"
#include "Platform/General/Editor/EditorEntityEditor.h"

Me::Editor::GL::EditorRendererGL::EditorRendererGL(Renderer::GL::RenderLayerGL* a_renderLayer)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_imguiIO = &ImGui::GetIO();	
	m_imguiIO->IniFilename = "Resources/EditorLayout/Default_Layout.ini";

    m_imguiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_imguiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	
	static ImWchar s_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig config;
	config.MergeMode = true;

	m_imguiIO->Fonts->AddFontDefault();
	m_imguiIO->Fonts->AddFontFromFileTTF("Resources/Fonts/fontawesome-webfont.ttf", 12.0f, &config, s_ranges); // Merge icon font
	
	ImGuiStyle& style = ImGui::GetStyle();

	if(m_imguiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
#ifdef PLATFORM_WINDOWS
	ImGui_ImplWin32_Init(static_cast<WindowsWindow*>(a_renderLayer->GetWindow())->GetWindowHandle());
#elif PLATFORM_LINUX

#endif

    ImGui_ImplOpenGL3_Init("#version 330");
    
	EditorToolbar* toolbar = new EditorToolbar(*a_renderLayer->GetWindow());
	AddWidget(*toolbar);
	EntityHierarchy* entHierarchy = new EntityHierarchy(*a_renderLayer->GetWindow());
	AddWidget(*entHierarchy);
	EntityEditor* entEditor = new EntityEditor(*entHierarchy);
	AddWidget(*entEditor);

	m_renderLayer = a_renderLayer;
}

void Me::Editor::GL::EditorRendererGL::Clear()
{
    ImGui_ImplOpenGL3_NewFrame();
#ifdef PLATFORM_WINDOWS

	ImGui_ImplWin32_NewFrame();

#elif PLATFORM_LINUX

#endif

	ImGui::NewFrame();
}

void Me::Editor::GL::EditorRendererGL::Populate()
{
	ImGui::DockSpaceOverViewport(0, ImGuiDockNodeFlags_PassthruCentralNode);

	Math::Vec2 size = m_renderLayer->GetWindow()->GetSize();
	m_imguiIO->DisplaySize = ImVec2(size.m_x,size.m_y);

	for(int i = 0; i < m_editorWidgets.size();i++)
	{
		m_editorWidgets[i]->Draw();
	} 
	
	ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	if (m_imguiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{            
		ImGui::UpdatePlatformWindows();
	}
}