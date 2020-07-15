#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	namespace renderer
	{
		class DeviceDx12;

		class CommandListDx12
		{
		public:
			CommandListDx12(D3D12_COMMAND_LIST_TYPE,math::Vec2);
			~CommandListDx12();

			void Close();
			void Reset(unsigned int);
			
			inline ID3D12GraphicsCommandList* GetList() { return m_cmdList.Get(); }
			void SetViewPort(int);
			void SetViewAndScissor(math::Vec2);
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCurrentAllocator(unsigned int);

		private:
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateAlloc(D3D12_COMMAND_LIST_TYPE);
			Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList;
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator[3];

			D3D12_RECT m_scissorRect;
			D3D12_VIEWPORT m_viewport;
		};
	}
}