#pragma once
#include "../Common/CommandList.h"

class Dx12_Device;
class Dx12_PSO;

class Dx12_CommandList : public CommandList
{
public:
	Dx12_CommandList(D3D12_COMMAND_LIST_TYPE, const Dx12_Device&, int a_w, int a_h);

	virtual void Reset(int) override;
	virtual void Close() override;
	virtual void Draw(RenderItem* a_item) override;
	
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCurrentAllocator(int);

	ID3D12GraphicsCommandList* GetList();
	Dx12_PSO* GetPSO();
	void SetSignature();
	void SetViewPort(int);
	void SetViewAndScissor(int a_w, int a_h);

private:
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateAlloc(const Dx12_Device&, D3D12_COMMAND_LIST_TYPE);
	void CreateRootSignature(const Dx12_Device&);

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator[gs_frameBufferCount];

	Dx12_PSO* m_pso;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_signature;

	D3D12_RECT m_scissorRect;
	D3D12_VIEWPORT m_viewport;
};

