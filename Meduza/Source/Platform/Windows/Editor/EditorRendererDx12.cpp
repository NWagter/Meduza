#include "MePCH.h"
#include "Platform/Windows/Editor/EditorRendererDx12.h"


#include "Platform/Windows/Graphics/RenderLayerDx12.h"
#include "Platform/Windows/Graphics/Context.h"
#include "Platform/Windows/Graphics/Descriptor.h"
#include "Platform/Windows/Graphics/CommandList.h"

#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>


Me::Editor::Dx12::EditorRendererDx12::EditorRendererDx12(Me::Renderer::Dx12::RenderLayerDx12* a_renderLayer)
{
    m_renderLayer = a_renderLayer;
    // Init ImGui
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	m_imGuiContext = ImGui::CreateContext();
	m_imGuiIO = &ImGui::GetIO();

	// Set font
	m_imGuiIO->Fonts->AddFontDefault();
    
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
}

void Me::Editor::Dx12::EditorRendererDx12::Clear()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Me::Editor::Dx12::EditorRendererDx12::Populate()
{
	ImGui::ShowDemoWindow();


	ImGui::EndFrame();
	// Render ImGui
	ID3D12DescriptorHeap* imGuiHeap[] = { m_renderLayer->GetSRV().GetHeap().Get() };
	m_renderLayer->GetCmd().GetList()->SetDescriptorHeaps(_countof(imGuiHeap), imGuiHeap);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_renderLayer->GetCmd().GetList());
}