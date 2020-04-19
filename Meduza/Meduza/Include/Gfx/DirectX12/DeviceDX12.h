#pragma once

#include "Gfx/Core/Renderer.h"

namespace meduza
{
	namespace renderer
	{

		class DeviceDX12
		{
		public:
			DeviceDX12();
			~DeviceDX12();

		private:
			Microsoft::WRL::ComPtr<ID3D12Device> m_device;
			Microsoft::WRL::ComPtr<IDXGIFactory> m_factory;
		};

	}
}