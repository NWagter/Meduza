#pragma once

namespace meduza
{
	namespace renderer
	{
		class DescriptorDx12;

		class DepthStencilDx12
		{
		public:
			DepthStencilDx12(int, int);
			void SetBuffer(int, int);
			~DepthStencilDx12();

			D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
			Microsoft::WRL::ComPtr<ID3D12Resource> GetBuffer() { return m_dsBuffer; }
		private:
			Microsoft::WRL::ComPtr<ID3D12Resource> m_dsBuffer;
			DXGI_FORMAT m_dsFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
			DescriptorDx12* m_dsv;
		};
	}
}