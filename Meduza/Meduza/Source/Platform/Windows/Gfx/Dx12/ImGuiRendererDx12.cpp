#include "mePch.h"

#include "Platform/General/Utils/MeduzaHelper.h"

#include "Platform/Windows/Gfx/Dx12/ImGuiRendererDx12.h"

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"
#include "Platform/Windows/Gfx/Dx12/CommandListDx12.h"
#include "Platform/Windows/Gfx/Dx12/DescriptorDx12.h"

meduza::ImGuiRendererDx12::ImGuiRendererDx12(renderer::Renderer& a_renderer)
{
	m_renderer = dynamic_cast<renderer::RendererDx12*>(&a_renderer);
	auto device = m_renderer->GetContext().GetDevice();

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NumDescriptors = 1;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	heapDesc.NodeMask = 0;

	m_GuiHeap = new renderer::DescriptorDx12(heapDesc, *device);

	ImGui_ImplDX12_Init(
		device->GetDevice(),
		GS_FRAMEBUFFERS,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		m_GuiHeap->GetHeap().Get(),
		m_GuiHeap->GetHeap().Get()->GetCPUDescriptorHandleForHeapStart(),
		m_GuiHeap->GetHeap().Get()->GetGPUDescriptorHandleForHeapStart()
	);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

meduza::ImGuiRendererDx12::~ImGuiRendererDx12()
{
	ImGui_ImplDX12_Shutdown();
	delete m_GuiHeap;
}

void meduza::ImGuiRendererDx12::Clear()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void meduza::ImGuiRendererDx12::Render()
{
	auto cmd = m_renderer->GetCmd().GetList();

	ID3D12DescriptorHeap* imGuiHeap[] = { m_GuiHeap->GetHeap().Get() };
	cmd->SetDescriptorHeaps(_countof(imGuiHeap), imGuiHeap);

	// Render ImGui
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmd);
}
