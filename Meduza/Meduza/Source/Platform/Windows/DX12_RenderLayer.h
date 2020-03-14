#pragma once
#include "Gfx/RenderLayer.h"

#include "DX12_UploadBuffer.h"

struct ImGuiContext;
struct ImGuiIO;
namespace cr { class IDrawable; }

namespace cr {

	class WinWindow;
	class Camera;

	class DX12_Device;
	class DX12_SwapChain;
	class DX12_CommandList;
	class DX12_CommandQueue;
	class DX12_Descriptor;
	class DX12_PSO;
	class DX12_RootSignature;
	class DX12_Mesh;

	struct RenderItem;

	class DX12_RenderLayer : public RenderLayer {
	public:
		DX12_RenderLayer(Window&);
		virtual ~DX12_RenderLayer();

		virtual void Clear(float[4]) override;
		virtual void Render() override;
		virtual void Draw(IDrawable*) override; // Require a Drawable which contains data : Transform, VertexBuffer, IndexBuffer, Material etc.
		virtual void Update(float) override;
		virtual void InitImGui() override;

	private:
		float* m_cColour;
		void Resize();
		void GeneratePrimitives();
		void ClearRenderItems();

		WinWindow* m_window;

		DX12_Device* m_device;
		DX12_SwapChain* m_swapChain;
		DX12_CommandQueue* m_cmdQueue;
		DX12_CommandList* m_cmdList;
		DX12_Descriptor* m_rtv;
		DX12_Descriptor* m_srv;
		DX12_Descriptor* m_cbv[gs_numBuffers];
		DX12_UploadBuffer<InstanceBuffer>* m_instanceBuffer[gs_numBuffers];
		DX12_UploadBuffer<ConstantBuffer>* m_cBuffer[gs_numBuffers];
		DX12_PSO* m_pso;
		DX12_RootSignature* m_rSignature;

		std::vector<RenderItem*> m_renderables;
		std::vector<DX12_Mesh*> m_meshes;

		ImGuiContext* m_imGuiContext;
		ImGuiIO* m_imGuiIO;

		int m_instanceItems = 0;
	};
}
