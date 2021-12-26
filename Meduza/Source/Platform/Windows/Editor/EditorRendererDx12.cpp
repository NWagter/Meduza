#include "MePCH.h"
#include "Platform/Windows/Editor/EditorRendererDx12.h"


#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include "Platform/Windows/Graphics/ContextDx.h"
#include "Platform/Windows/Graphics/Descriptor.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/Helper/TextureLoader.h"

#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

#include "Platform/General/Editor/EditorToolbar.h"
#include "Platform/General/Editor/EditorEntityHierarchy.h"
#include "Platform/General/Editor/EditorEntityEditor.h"
#include "Platform/General/Editor/EditorViewport.h"
#include "Platform/General/Editor/EditorStats.h"
#include "Platform/General/Editor/EditorResourceBrowser.h"
#include "Platform/General/Editor/EditorAssetBrowser.h"


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
    
	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 2;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

	m_srv = new Renderer::Dx12::Descriptor(srvDesc, a_renderLayer->GetDevice());

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(a_renderLayer->GetContext().GetHWND());
	ImGui_ImplDX12_Init(
		a_renderLayer->GetDevice().GetDevice(),
		3,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		m_srv->GetHeap().Get(),
		m_srv->GetHeap().Get()->GetCPUDescriptorHandleForHeapStart(),
		m_srv->GetHeap().Get()->GetGPUDescriptorHandleForHeapStart()
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
	EditorStats* stats = new EditorStats(*a_renderLayer);
	AddWidget(stats);
	EditorResourceBrowser* resourceBrowser = new EditorResourceBrowser();
	AddWidget(resourceBrowser);
	EditorAssetBrowser* assetBrowser = new EditorAssetBrowser();
	AddWidget(assetBrowser);
}

Me::Editor::Dx12::EditorRendererDx12::~EditorRendererDx12()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete m_srv;
	
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
	auto cmd = m_renderLayer->GetCmd();

	ID3D12DescriptorHeap* inlineDesHeap[] = { m_srv->GetHeap().Get() };
	cmd.GetList()->SetDescriptorHeaps(_countof(inlineDesHeap), inlineDesHeap);
	for(int i = 0; i < m_editorWidgets.size();i++)
	{
		if (i == 3)
		{
			ME_LOG("STOP! \n");
		}

		m_editorWidgets[i]->Draw();
	}

	ImGui::Render();

	//ImGui::Begin("DirectX12 Texture Test");
	//ImGui::Text("CPU handle = %p", folderHandleCPU.ptr);
	//ImGui::Text("GPU handle = %p", folderHandle.ptr);
	//ImGui::Text("size = %f x %f", folderTexture->GetSize().m_x, folderTexture->GetSize().m_y);
	//ImGui::Image((ImTextureID)folderHandle.ptr, { 256, 256 });
	//ImGui::End();

	// Render ImGui
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmd.GetList());

	if (m_imguiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
	}
}