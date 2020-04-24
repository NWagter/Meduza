#pragma once

namespace meduza
{
	namespace renderer
	{
		class DeviceDx12;
		class CommandQueueDx12;

		class FenceDx12
		{
		public:
			FenceDx12(DeviceDx12&);
			~FenceDx12();

			void WaitForFence(UINT);

			void Flush(CommandQueueDx12&);


			Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
		private:
			unsigned int m_currentFence = 0;
		};
	}
}