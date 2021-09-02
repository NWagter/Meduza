#include "MePCH.h"

#include "Platform/General/Editor/EditorRendererGL.h"
#include "Platform/General/Graphics/RenderLayerGL.h"

#include <imgui_impl_opengl3.h>

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include <imgui_impl_win32.h>
#elif PLATFORM_LINUX

#endif

#include "Platform/General/Editor/EditorEntityHierarchy.h"
#include "Platform/General/Editor/EditorEntityEditor.h"

Me::Editor::GL::EditorRendererGL::EditorRendererGL(Renderer::GL::RenderLayerGL* a_renderLayer)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
#ifdef PLATFORM_WINDOWS
	ImGui_ImplWin32_Init(static_cast<WindowsWindow*>(a_renderLayer->GetWindow())->GetWindowHandle());
#elif PLATFORM_LINUX

#endif

    ImGui_ImplOpenGL3_Init("#version 330");
    
	EntityHierarchy* entHierarchy = new EntityHierarchy();
	AddWidget(*entHierarchy);
	EntityEditor* entEditor = new EntityEditor(*entHierarchy);
	AddWidget(*entEditor);
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
	for(int i = 0; i < m_editorWidgets.size();i++)
	{
		m_editorWidgets[i]->Draw();
	}

	ImGui::EndFrame();

	ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}