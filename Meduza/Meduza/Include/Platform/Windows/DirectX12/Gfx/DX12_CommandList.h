#pragma once

#include "Gfx/GfxHelper.h"

namespace mr
{

	class DX12_Device;
	class DX12_PipelineStateObject;
	class DX12_SignatureRoot;
	struct RenderItem;

	class DX12_CommandList
	{
	public:
		DX12_CommandList(D3D12_COMMAND_LIST_TYPE, DX12_Device&, int, int);
		~DX12_CommandList();

		void Close();
		void Reset(int, DX12_PipelineStateObject*);
		void Draw(RenderItem*, ID3D12Resource*);

		inline ID3D12GraphicsCommandList* GetList() { return m_cmdList.Get(); }
		void SetViewPort(int);
		void SetViewAndScissor(int, int);
		void SetPSO(DX12_PipelineStateObject*);
		void SetSignature(DX12_SignatureRoot*);
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCurrentAllocator(int);

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateAlloc(DX12_Device&, D3D12_COMMAND_LIST_TYPE);
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator[gs_framebufferCount];

		D3D12_RECT m_scissorRect;
		D3D12_VIEWPORT m_viewport;
	};
}