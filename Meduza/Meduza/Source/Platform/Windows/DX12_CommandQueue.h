#pragma once

namespace cr {

	class DX12_Device;
	class DX12_CommandList;
	class DX12_Fence;

	class DX12_CommandQueue {
	public:
		DX12_CommandQueue(D3D12_COMMAND_QUEUE_DESC, DX12_Device&);
		~DX12_CommandQueue();
		inline ID3D12CommandQueue* GetQueue() { return m_queue.Get(); }
		virtual void ExecuteList(DX12_CommandList*);
		void Flush();

	private:

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_queue;
		DX12_Fence* m_fence;
	};
}