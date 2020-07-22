#pragma once

#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/Windows/Window/Dx12/ContextDx12.h"
#include "Platform/Windows/Gfx/Dx12/DeviceDx12.h"

namespace meduza
{
	namespace renderer
	{
		template<typename T>
		class UploadBufferDx12
		{
		public:
			UploadBufferDx12(bool a_const)
			{
				unsigned int byteSize = sizeof(T);

				if (a_const)
				{
					byteSize = (sizeof(T) + 255) & ~255;
				}

				m_constBufferAlignment = byteSize;

				CD3DX12_HEAP_PROPERTIES props = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
				CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(m_constBufferAlignment * m_elementCount);

				auto device = RendererDx12::GetRenderer()->GetContext().GetDevice();

				device->GetDevice()->CreateCommittedResource(
					&props,
					D3D12_HEAP_FLAG_NONE,
					&buffer,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(&m_bufferResource));
				m_bufferResource->SetName(L"Constant Buffer Upload Resource Heap");

				m_bufferResource->Map(0, nullptr, reinterpret_cast<void**>(&m_bufferData));
			}
			~UploadBufferDx12() = default;

			void CopyData(int a_alignment, const T& a_data)
			{
				memcpy(&m_bufferData[a_alignment], &a_data, sizeof(T));
			}

			inline UINT8* GetBufferGPUAdress() { return m_bufferDataGPUAdress; }
			inline Microsoft::WRL::ComPtr<ID3D12Resource> GetResource() { return m_bufferResource; }
			inline int GetBufferAlignment() { return m_constBufferAlignment; }

			inline int GetElementCount() { return m_elementCount; }
			void SetElementCount(int a_size, bool a_const)
			{
				unsigned int byteSize = sizeof(T);

				if (a_const)
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

				auto device = RendererDx12::GetRenderer()->GetContext().GetDevice();

				device->GetDevice()->CreateCommittedResource(
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
			BYTE* m_bufferData = nullptr; //const buffer data

			UINT8* m_bufferDataGPUAdress = nullptr; // this is a pointer to the memory location we get when we map our constant buffer
			int m_elementCount = 256;
			int m_constBufferAlignment = sizeof(T);
		};
	}
}