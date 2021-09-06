#pragma once
namespace Me
{
    namespace Math
    {
        namespace Dx12
        {
            static inline DirectX::XMFLOAT4X4 Identity4x4()
            {
                static DirectX::XMFLOAT4X4 s_i(
                    1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);

                return s_i;
            }
        }
    }
    namespace Helper
    {
        namespace Dx12
        {
            struct TextureData
            {
                unsigned int m_resourceId;
                unsigned int m_srvOffset = 0;

                std::string m_filename;
                std::string m_filePath;

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