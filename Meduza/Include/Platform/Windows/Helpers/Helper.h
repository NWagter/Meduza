#pragma once
namespace Me
{
    namespace Helper
    {
        namespace Dx12
        {
            class Helper
            {
                public:
				static Microsoft::WRL::ComPtr<ID3D12Resource> CreateBuffer(ID3D12Device*,
					ID3D12GraphicsCommandList*,
					const void*,
					UINT64,
					Microsoft::WRL::ComPtr<ID3D12Resource>&);

				static Microsoft::WRL::ComPtr<ID3D12Resource> CopyBuffer(ID3D12Device*,
					ID3D12GraphicsCommandList*,
					const void*,
					UINT64,
					Microsoft::WRL::ComPtr<ID3D12Resource>&);
            };
        }
    }
}