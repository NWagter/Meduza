#include "MePCH.h"
#include "Platform/Windows/Helper/Helper.h"
#include "Platform/Windows/Helper/TextureLoader.h"

#include "Platform/General/FileSystem/FileSystem.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/Graphics/Descriptor.h"

#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include <codecvt>
#include <regex>

static constexpr size_t MAX_TEXTURES = 8;

Me::Helper::Dx12::TextureLoader::TextureLoader(Renderer::Dx12::Device& a_device, Renderer::Dx12::CommandList& a_cmd)
{
	m_device = &a_device;
	m_cmd = &a_cmd;
	//SRVHeap(Descriptor)
	D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 256;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;

    SRV srv;
    srv.m_srv = new Renderer::Dx12::Descriptor(srvDesc, a_device);

    m_srvs.push_back(srv);
    m_currentID = 0;
}

Me::Helper::Dx12::TextureLoader::~TextureLoader()
{
    for(auto srv : m_srvs)
    {
        for(auto t : srv.m_textures)
        {
            t = nullptr;
        }

        delete srv.m_srv;
    }

    m_srvs.clear();
}

const Me::Helper::Dx12::TextureReturnData* Me::Helper::Dx12::TextureLoader::LoadTexture(std::string a_file)
{
    TextureReturnData* data = new TextureReturnData();

    std::string ext = Files::FileSystem::GetFileExtention(a_file);
    data->m_textureData = CreateTexture(a_file, ext);

    data->m_srvId = m_currentID;
    
	LoadToSRV(*data->m_textureData, data->m_srvId);

    data->m_size = Math::Vec2(float(data->m_textureData->m_resource->GetDesc().Width), float(data->m_textureData->m_resource->GetDesc().Height));

    ME_CORE_LOG("Loaded %s with Succes! \n", data->m_textureData->m_filename.c_str());

    return data;
}

Me::Helper::Dx12::TextureData* Me::Helper::Dx12::TextureLoader::CreateTexture(std::string a_file, std::string a_ext)
{
    TextureData* texture = new TextureData();
    texture->m_filename = Files::FileSystem::GetFileName(a_file);

	auto path = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(a_file);
    
	HRESULT hr = S_OK;

    if(a_ext == "dds")
    {
		hr = DirectX::CreateDDSTextureFromFile12(
			m_device->GetDevice(),
			m_cmd->GetList(),
			path.c_str(),
			texture->m_resource,
			texture->m_uploadHeap);

            
        if (hr != S_OK)
        {
            delete texture;
            ME_GFX_ASSERT_M(false, "Failed to create Texture!");
        }

    }
    else if(a_ext == "bmp" || a_ext == "png" || a_ext == "jpg")
    {
	    std::unique_ptr<uint8_t[]> txtData;
		D3D12_SUBRESOURCE_DATA subresources;

		hr = DirectX::LoadWICTextureFromFile(
			m_device->GetDevice(),
			path.c_str(),
			texture->m_resource.ReleaseAndGetAddressOf(),
			txtData,
			subresources);

        if (hr != S_OK)
        {
            delete texture;
            ME_GFX_ASSERT_M(false, "Failed to create Texture!");
        }

        const UINT64 uploadBufferSize = GetRequiredIntermediateSize(texture->m_resource.Get(), 0, 1);
		CD3DX12_HEAP_PROPERTIES prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		CD3DX12_RESOURCE_DESC buffer = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);

		// Create the GPU upload buffer.		
		m_device->GetDevice()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&buffer,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(texture->m_uploadHeap.GetAddressOf()));

		UpdateSubresources(m_cmd->GetList(),
			texture->m_resource.Get(),
			texture->m_uploadHeap.Get(), 0, 0, 1, &subresources);

		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(texture->m_resource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		m_cmd->GetList()->ResourceBarrier(1, &barrier);
    }
    else
    {
        ME_GFX_ASSERT_M(false, "Don't Reconize the extention!");
    }


    SRVOffset(&texture->m_srvOffset, *texture);

    return texture;
}

void Me::Helper::Dx12::TextureLoader::SRVOffset(unsigned int* a_srv, TextureData& a_texture)
{
    auto srv = m_srvs.at(m_currentID);

    if(srv.m_textures.size() < MAX_TEXTURES)
    {
        *a_srv = unsigned int(srv.m_textures.size());
        srv.m_textures.push_back(&a_texture);
    }
    else
    {
        D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
        srvDesc.NumDescriptors = 256;
        srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        srvDesc.NodeMask = 0;

        SRV srv;
        srv.m_srv = new Renderer::Dx12::Descriptor(srvDesc, *m_device);
        m_srvs.push_back(srv);

        m_currentID++;
        SRVOffset(a_srv, a_texture);
    }
}

void Me::Helper::Dx12::TextureLoader::LoadToSRV(TextureData& a_texture, unsigned int a_srvId)
{
    auto t = &a_texture;
    auto srv = m_srvs.at(a_srvId).m_srv;
    CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(srv->GetHeap()->GetCPUDescriptorHandleForHeapStart());

	if (t->m_srvOffset != 0)
	{
		hDescriptor.Offset(t->m_srvOffset, srv->GetSize());
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	auto tResource = t->m_resource;

	srvDesc.Texture2D.MipLevels = tResource->GetDesc().MipLevels;
	srvDesc.Format = tResource->GetDesc().Format;

	m_device->GetDevice()->CreateShaderResourceView(tResource.Get(), &srvDesc, hDescriptor);
}