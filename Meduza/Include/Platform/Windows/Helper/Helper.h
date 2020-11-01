#pragma once
namespace Me
{
    namespace Helper
    {
        namespace Dx12
        {
            struct TextureData
            {
                unsigned int m_resourceId;
                unsigned int m_srvOffset = 0;

                std::string m_filename;

                Microsoft::WRL::ComPtr<ID3D12Resource> m_resource = nullptr;
                Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadHeap = nullptr;
            };

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