#pragma once

#include "Platform/Windows/DX12_UploadBuffer.h"

#include "Platform/Windows/DX12_Device.h"
#include "Platform/Windows/DX12_Descriptor.h"


namespace cr {

	template<typename T>
	class DX12_UploadBuffer {
	public:
		DX12_UploadBuffer(DX12_Device& a_device, bool a_const)
		{
			unsigned int byteSize = sizeof(T);

			if (a_const)
			{
				byteSize = (sizeof(T) + 255) & ~255;
			}

			m_constBufferAlignment = byteSize;

			CD3DX12_HEAP_PROPERTIES props = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(m_constBufferAlignment * m_elementCount);

			a_device.GetDevice()->CreateCommittedResource(
				&props,
				D3D12_HEAP_FLAG_NONE,
				&buffer,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_bufferResource));
			m_bufferResource->SetName(L"Constant Buffer Upload Resource Heap");

			m_bufferResource->Map(0, nullptr, reinterpret_cast<void**>(&m_bufferData));
		}

		void CopyData(int a_alignment, const T& a_data)
		{
			memcpy(&m_bufferData[a_alignment], &a_data, sizeof(T));
		}

		inline UINT8* GetBufferGPUAdress() { return m_bufferDataGPUAdress; }
		inline Microsoft::WRL::ComPtr<ID3D12Resource> GetResource() { return m_bufferResource; }
		inline int GetBufferAlignment() { return m_constBufferAlignment; }
		
		inline int GetElementCount() { return m_elementCount; }
		void SetElementCount(DX12_Device& a_device, int a_size, bool a_const)
		{
			unsigned int byteSize = sizeof(T);

			if (a_const == true)
			{
				byteSize = (sizeof(T) + 255) & ~255;
			}

			m_constBufferAlignment = byteSize;

			m_bufferResource.Reset();

			CD3DX12_HEAP_PROPERTIES props = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

			int size = 256;
			if (a_size > 256)
			{
				size = a_size;
			}
			m_elementCount = size;

			CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(m_constBufferAlignment * m_elementCount);

			a_device.GetDevice()->CreateCommittedResource(
				&props,
				D3D12_HEAP_FLAG_NONE,
				&buffer,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_bufferResource));
			m_bufferResource->SetName(L"Constant Buffer Upload Resource Heap");

			m_bufferResource->Map(0, nullptr, reinterpret_cast<void**>(&m_bufferData));
		};

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_bufferResource;
		BYTE* m_bufferData; //const buffer data

		UINT8* m_bufferDataGPUAdress; // this is a pointer to the memory location we get when we map our constant buffer
		int m_elementCount = 256;
		int m_constBufferAlignment = (sizeof(T) + 255) & ~255;
	};
}