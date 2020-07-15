#pragma once

namespace meduza
{
	namespace renderer
	{
		class DeviceDx12;
		class CommandListDx12;
		class FenceDx12;

		class CommandQueueDx12
		{
		public:
			CommandQueueDx12(D3D12_COMMAND_QUEUE_DESC, DeviceDx12* = nullptr);
			~CommandQueueDx12();

			inline D3D12_COMMAND_QUEUE_DESC GetDesc() { return m_description; }
			inline ID3D12CommandQueue* GetQueue() { return m_queue.Get(); }
			void ExecuteList(CommandListDx12*);
			void Flush();

		private:

			Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_queue;
			D3D12_COMMAND_QUEUE_DESC m_description;

			FenceDx12* m_fence;
		};
	}
}