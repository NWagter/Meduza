#include "MePCH.h"
#include "Platform/Windows/Editor/EditorRendererDx12.h"


#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include "Platform/Windows/Graphics/ContextDx.h"
#include "Platform/Windows/Graphics/Descriptor.h"
#include "Platform/Windows/Graphics/CommandList.h"

#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

#include "Platform/General/Editor/EditorToolbar.h"
#include "Platform/General/Editor/EditorEntityHierarchy.h"
#include "Platform/General/Editor/EditorEntityEditor.h"
#include "Platform/General/Editor/EditorViewport.h"


Me::Editor::Dx12::EditorRendererDx12::EditorRendererDx12(Me::Renderer::Dx12::RenderLayerDx12* a_renderLayer)
{
    m_renderLayer = a_renderLayer;
    // Init ImGui
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
	
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
    if (m_imguiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    
    auto srv = a_renderLayer->GetSRV().GetHeap();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(a_renderLayer->GetContext().GetHWND());
	ImGui_ImplDX12_Init(
		a_renderLayer->GetDevice().GetDevice(),
		3,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		srv.Get(),
		srv.Get()->GetCPUDescriptorHandleForHeapStart(),
		srv.Get()->GetGPUDescriptorHandleForHeapStart()
	);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	EditorToolbar* toolbar = new EditorToolbar(*a_renderLayer->GetWindow());
	AddWidget(toolbar);
	EntityHierarchy* entHierarchy = new EntityHierarchy(*a_renderLayer->GetWindow());
	AddWidget(entHierarchy);
	EntityEditor* entEditor = new EntityEditor(*entHierarchy);
	AddWidget(entEditor);
	EditorViewport* viewPort = new EditorViewport(*entEditor, *toolbar, *m_renderLayer);
	AddWidget(viewPort);
}

Me::Editor::Dx12::EditorRendererDx12::~EditorRendererDx12()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	
}

void Me::Editor::Dx12::EditorRendererDx12::Clear()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Me::Editor::Dx12::EditorRendererDx12::Update(float a_dt)
{
	for (int i = 0; i < m_editorWidgets.size(); i++)
	{
		m_editorWidgets[i]->Update(a_dt);
	}
}

void Me::Editor::Dx12::EditorRendererDx12::Populate()
{
	ImGui::DockSpaceOverViewport(0, ImGuiDockNodeFlags_PassthruCentralNode);

	for(int i = 0; i < m_editorWidgets.size();i++)
	{
		m_editorWidgets[i]->Draw();
	}

	ImGui::EndFrame();
	// Render ImGui
	ID3D12DescriptorHeap* imGuiHeap[] = { m_renderLayer->GetSRV().GetHeap().Get() };
	m_renderLayer->GetCmd().GetList()->SetDescriptorHeaps(_countof(imGuiHeap), imGuiHeap);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_renderLayer->GetCmd().GetList());

	
	if (m_imguiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
	}
}