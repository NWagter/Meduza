#include "MePCH.h"
#include "Platform/Windows/Helper/Helper.h"

Microsoft::WRL::ComPtr<ID3D12Resource> Me::Helper::Dx12::Helper::CreateBuffer(
	ID3D12Device* a_device,
	ID3D12GraphicsCommandList* a_cmdList,
	const void* a_initData,
	UINT64 a_byteSize,
	Microsoft::WRL::ComPtr<ID3D12Resource>& a_uploadBuffer)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;

	CD3DX12_HEAP_PROPERTIES heapDefault = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(a_byteSize);

	HRESULT hr = S_OK;

	hr = a_device->CreateCommittedResource(
		&heapDefault,
		D3D12_HEAP_FLAG_NONE,
		&buffer,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer));

	defaultBuffer->SetName(L"Default Buffer Resource Heap");

	if(hr != S_OK)
	{
		ME_GFX_LOG("ERROR! \n");
	}

	CD3DX12_HEAP_PROPERTIES heapUpload = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	hr = a_device->CreateCommittedResource(
		&heapUpload,
		D3D12_HEAP_FLAG_NONE,
		&buffer,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&a_uploadBuffer));

	a_uploadBuffer->SetName(L"UploadBuffer Resource Heap");

	if(hr != S_OK)
	{
		ME_GFX_LOG("ERROR! \n");
	}

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = a_initData;
	subResourceData.RowPitch = a_byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get()
		, D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_COPY_DEST);

	a_cmdList->ResourceBarrier(1, &barrier);

	UpdateSubresources<1>(a_cmdList, defaultBuffer.Get(), a_uploadBuffer.Get(), 0, 0, 1, &subResourceData);

	barrier = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

	a_cmdList->ResourceBarrier(1, &barrier);


	return defaultBuffer;
}

Microsoft::WRL::ComPtr<ID3D12Resource> Me::Helper::Dx12::Helper::CopyBuffer(
	ID3D12Device* a_device,
	ID3D12GraphicsCommandList* a_cmdList,
	const void* a_initData,
	UINT64 a_byteSize,
	Microsoft::WRL::ComPtr<ID3D12Resource>& a_uploadBuffer)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;

	CD3DX12_HEAP_PROPERTIES heapDefault = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(a_byteSize);

	a_device->CreateCommittedResource(
		&heapDefault,
		D3D12_HEAP_FLAG_NONE,
		&buffer,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer));
	defaultBuffer->SetName(L"Default CopyBuffer Resource Heap");

	CD3DX12_HEAP_PROPERTIES heapUpload = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	a_device->CreateCommittedResource(
		&heapUpload,
		D3D12_HEAP_FLAG_NONE,
		&buffer,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&a_uploadBuffer));
	a_uploadBuffer->SetName(L"CopyBuffer Resource Heap");

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = a_initData;
	subResourceData.RowPitch = a_byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get()
		, D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_COPY_DEST);

	a_cmdList->ResourceBarrier(1, &barrier);

	UpdateSubresources<1>(a_cmdList, defaultBuffer.Get(), a_uploadBuffer.Get(), 0, 0, 1, &subResourceData);

	barrier = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COPY_SOURCE);

	a_cmdList->ResourceBarrier(1, &barrier);


	return defaultBuffer;
}
