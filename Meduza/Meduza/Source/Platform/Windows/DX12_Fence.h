#pragma once

namespace cr {

	class DX12_Device;
	class DX12_CommandQueue;

	class DX12_Fence {
	public:
		DX12_Fence(DX12_Device&);
		~DX12_Fence();

		void WaitForFence(UINT);

		void Flush(DX12_CommandQueue&);


		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
	private:
		unsigned int m_currentFence = 0;
	};
}