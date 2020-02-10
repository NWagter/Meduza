#pragma once
#include "../Common/CommandList.h"

class Dx12_Device;
class Dx12_PSO;
class Dx12_RootSignature;

class Dx12_CommandList : public CommandList
{
public:
	Dx12_CommandList(D3D12_COMMAND_LIST_TYPE, const Dx12_Device&, int a_w, int a_h);
	~Dx12_CommandList();

	virtual void Reset(int, PSO*) override;
	virtual void Close() override;
	virtual void Draw(RenderItem* a_item) override;
	
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCurrentAllocator(int);

	ID3D12GraphicsCommandList* GetList();
	void SetPSO(Dx12_PSO*);
	void SetSignature(Dx12_RootSignature*);
	void SetViewPort(int);
	void SetViewAndScissor(int a_w, int a_h);

private:
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateAlloc(const Dx12_Device&, D3D12_COMMAND_LIST_TYPE);
	void CreateRootSignature(const Dx12_Device&);

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator[gs_frameBufferCount];


	D3D12_RECT m_scissorRect;
	D3D12_VIEWPORT m_viewport;
};

