#include "MePCH.h"
#include "Platform/Windows/Graphics/RenderLayerDx12.h"

#include "Platform/Windows/Helper/Helper.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/Graphics/Context.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/Graphics/CommandQueue.h"
#include "Platform/Windows/Graphics/Descriptor.h"
#include "Platform/Windows/Graphics/DepthStencil.h"
#include "Platform/Windows/Graphics/InstancedRenderCall.h"

#include "Platform/Windows/Resources/Mesh.h"
#include "Platform/General/MeshLibrary.h"

#include "Platform/Windows/Resources/Shader.h"
#include "Platform/General/ShaderLibrary.h"

#include "Platform/Windows/Resources/Texture.h"
#include "Platform/General/TextureLibrary.h"
#include "Platform/Windows/Helper/TextureLoader.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

#define TEST_WITH_DX_DEBUG 1

Me::Renderer::Dx12::RenderLayerDx12::RenderLayerDx12(Me::Window* a_window)
{
    if(a_window == nullptr)
    {
        printf("Window is Null!");
        return;
    }

#if defined(_DEBUG)
	#if TEST_WITH_DX_DEBUG
	// Always enable the debug layer before doing anything DX12 related
	// so all possible errors generated while creating DX12 objects
	// are caught by the debug layer.
	Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
	debugInterface->EnableDebugLayer();
	#endif
#endif

    //cast the window into a WindowsWindow type
    m_window = dynamic_cast<WindowsWindow*>(a_window);
	
    m_device = new Device();
    m_context = new Context(m_window->GetWindowHandle(), m_device);
	m_window->SetContext(m_context);

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	m_queue = new CommandQueue(queueDesc, m_device);
    m_context->SetQueue(*m_queue);
    
	m_cmd.push_back(new CommandList(m_context->GetQueue()->GetDesc().Type, m_device, m_context->m_width, m_context->m_height));

    m_context->CreateSwapchain();
    
	m_textureLoader = new Helper::Dx12::TextureLoader(*m_device, GetCmd());

    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 3;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_rtv = new Descriptor(desc, *m_device);
	m_context->CreateRTV(*m_rtv);


    D3D12_DESCRIPTOR_HEAP_DESC srvDesc = {};
	srvDesc.NumDescriptors = 1;
	srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDesc.NodeMask = 0;
	
	m_srv = new Descriptor(srvDesc, *m_device);

	RECT rect;
	::GetClientRect(m_context->GetHWND(), &rect);
	int w = static_cast<int>(rect.right - rect.left);
	int h = static_cast<int>(rect.bottom - rect.top);

	m_dsBuffer = new DepthStencilBuffer(*m_device, GetCmd(), w, h);

	m_startUp = true;

	m_activeShader = nullptr;

	m_camBuffer = new Helper::Dx12::UploadBuffer<Helper::Dx12::CameraBuffer>(*m_device, true);
}

Me::Renderer::Dx12::RenderLayerDx12::~RenderLayerDx12()
{
    m_queue->Flush();

	delete m_textureLoader;
    delete m_context;
    delete m_device;
    delete m_queue;
	delete m_dsBuffer;
}

void Me::Renderer::Dx12::RenderLayerDx12::Clear(Colour a_colour)
{
	auto cmd = GetCmd();

	if(m_startUp)
	{
		m_startUp = false;
		m_queue->ExecuteList(&cmd);
		m_queue->Flush();
	}

	auto commandAllocator = cmd.GetCurrentAllocator(m_context->GetCurrentFrameIndex());
	auto backBuffer = m_context->GetCurrentBuffer();

    commandAllocator->Reset();
	cmd.Reset(m_context->GetCurrentFrameIndex(), m_activeShader);

    for (auto cL : m_cmd)
	{
		cL->m_closedList = false;
	}

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmd.GetList()->ResourceBarrier(1, &barrier);
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtv->GetHeap()->GetCPUDescriptorHandleForHeapStart(),
		m_context->GetCurrentFrameIndex(), m_rtv->GetSize());

	D3D12_CPU_DESCRIPTOR_HANDLE dvsHandle = m_dsBuffer->DepthStencilView();


	cmd.GetList()->ClearRenderTargetView(rtvHandle, a_colour.m_colour, 0, nullptr);
	cmd.GetList()->ClearDepthStencilView(dvsHandle,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	cmd.GetList()->OMSetRenderTargets(1, &rtvHandle, 1, &dvsHandle);

	
	m_renderables.clear();
	m_activeShader = nullptr;

	for(auto instanced : m_instancedRenderer)
	{
		instanced->ClearBuffer();
	}	
}

void Me::Renderer::Dx12::RenderLayerDx12::Present()
{
    m_context->SwapBuffers(GetCmd());
}

void Me::Renderer::Dx12::RenderLayerDx12::Submit(RenderComponent& a_renderable, TransformComponent& a_trans)
{
	// If no instanced Renderers we just create one
	BaseInstanced* instancedRenderer = nullptr;
	
	unsigned int srv = 0;
	unsigned int textureId = 0;
	if(a_renderable.m_texture != 0)
	{
		auto t = static_cast<Resources::Dx12::Texture*>(Resources::TextureLibrary::GetTexture(a_renderable.m_texture));	
		srv = t->GetSRVId();
		textureId = t->GetTexture().m_srvOffset;		
	}

	if(m_instancedRenderer.empty())
	{

		auto b = new InstancedRenderCall<Helper::Dx12::DefaultInstancedBuffer>(
			a_renderable.m_mesh, a_renderable.m_shader, srv, m_device);
		m_instancedRenderer.push_back(b);

		instancedRenderer = b;
	}
	else
	{
		for(auto iR : m_instancedRenderer)
		{

			if(	a_renderable.m_mesh == iR->GetMesh()
				&& a_renderable.m_shader == iR->GetShader()
				&& srv == iR->GetSRVID())
			{
				if(!iR->ReachedMaxSize())
				{
					instancedRenderer = iR;
					break;
				}
			}
		}

		if(instancedRenderer == nullptr)
		{		
			auto b = new InstancedRenderCall<Helper::Dx12::DefaultInstancedBuffer>(
				a_renderable.m_mesh, a_renderable.m_shader, srv, m_device);
			m_instancedRenderer.push_back(b);

			instancedRenderer = b;
		}
	}


	auto iB = Helper::Dx12::DefaultInstancedBuffer();

	iB.m_colour = DirectX::XMFLOAT4(a_renderable.m_colour.m_colour);
	iB.m_textureId = textureId;
	iB.m_textureCoords = DirectX::XMFLOAT4(a_renderable.m_textureCoords.m_xyzw);

	auto pos = a_trans.GetPosition();
	auto scale = a_trans.GetUniformedScale();
	auto rot = a_trans.GetRotation();

	const DirectX::XMMATRIX p = DirectX::XMMatrixTranslation(pos.m_x, pos.m_y, pos.m_z);
	const DirectX::XMMATRIX s = DirectX::XMMatrixScaling(scale, scale, scale);
	const DirectX::XMMATRIX r = DirectX::XMMatrixRotationRollPitchYaw(rot.m_x, rot.m_y, rot.m_z);
	const DirectX::XMMATRIX model = r * s * p;

	DirectX::XMStoreFloat4x4(&iB.m_model, DirectX::XMMatrixTranspose(model));

	static_cast<InstancedRenderCall<Helper::Dx12::DefaultInstancedBuffer>*>(instancedRenderer)->AddData(iB);


}

void Me::Renderer::Dx12::RenderLayerDx12::SetCamera(CameraComponent& a_cam, TransformComponent& a_trans)
{
	if(a_cam.m_cameraType == CameraType::Orthographic)
	{
		auto pos = a_trans.GetPosition();
		auto rot = a_trans.GetRotation().m_z;
			
		auto transMatrix = DirectX::XMMatrixTranslation(pos.m_x,pos.m_y,pos.m_z);
		auto rotMatrix = DirectX::XMMatrixRotationZ(rot);
		
		auto ortho = DirectX::XMMatrixOrthographicOffCenterLH(
				0, a_cam.m_size.m_x, 0, a_cam.m_size.m_y,
				a_cam.m_near, a_cam.m_far
			);
			
		auto viewProjection = DirectX::XMMatrixTranspose((transMatrix * rotMatrix) * ortho);

		Helper::Dx12::CameraBuffer cBuffer = Helper::Dx12::CameraBuffer();
		DirectX::XMStoreFloat4x4(&cBuffer.m_viewProjection, viewProjection);

		m_camBuffer->CopyData(0, cBuffer);
	}
	else if(a_cam.m_cameraType == CameraType::Perspective)
	{
		auto pos = a_trans.GetPosition();
		auto rot = a_trans.GetRotation();
			
		auto transMatrix = DirectX::XMMatrixTranslation(-pos.m_x,-pos.m_y,-pos.m_z);
		auto rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rot.m_pitch,rot.m_yaw,rot.m_roll);

		// build projection and view matrix
		DirectX::XMMATRIX projectionMat = DirectX::XMMatrixPerspectiveFovLH(45.0f*(3.14f/180.0f),
		a_cam.m_size.m_x / a_cam.m_size.m_y, a_cam.m_near, a_cam.m_far);

		auto viewProjection = DirectX::XMMatrixTranspose((transMatrix * rotMatrix) * projectionMat);

		Helper::Dx12::CameraBuffer cBuffer = Helper::Dx12::CameraBuffer();
		DirectX::XMStoreFloat4x4(&cBuffer.m_viewProjection, viewProjection);

		m_camBuffer->CopyData(0, cBuffer);
	}
}

void Me::Renderer::Dx12::RenderLayerDx12::Populate()
{
	GetCmd().SetViewPort(1);

	auto cmd = &GetCmd();

	unsigned int srvId = 0;
	Helper::Dx12::SRV srv = m_textureLoader->GetSRV(srvId);
	ID3D12DescriptorHeap* DescHeap[] = { srv.m_srv->GetHeap().Get() };
	cmd->GetList()->SetDescriptorHeaps(_countof(DescHeap), DescHeap);

	for(auto instanced : m_instancedRenderer)
	{
		// TODO : Get Material and set the correct SRV
		auto s = static_cast<Resources::Dx12::Shader*>(Resources::ShaderLibrary::GetShader(instanced->GetShader()));
		if(instanced->GetSRVID() != srvId)
		{
			srvId = instanced->GetSRVID();
			srv = m_textureLoader->GetSRV(srvId);
			ID3D12DescriptorHeap* inlineDesHeap[] = { srv.m_srv->GetHeap().Get() };
			cmd->GetList()->SetDescriptorHeaps(_countof(inlineDesHeap), inlineDesHeap);
		}

		if(m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
		{
			m_activeShader = s;
			m_activeShader->Bind();
		}

		cmd->GetList()->SetGraphicsRootDescriptorTable(0, srv.m_srv->GetHeap().Get()->GetGPUDescriptorHandleForHeapStart());
		
		cmd->GetList()->SetGraphicsRootConstantBufferView(1, m_camBuffer->GetResource().Get()->GetGPUVirtualAddress());
		instanced->Draw(cmd);
	}
}

Me::Renderer::Dx12::CommandList& Me::Renderer::Dx12::RenderLayerDx12::GetCmd(int a_id)
{
    auto cmd = m_cmd.at(a_id);
	if (cmd == nullptr)
	{
		return *cmd;
	}

	return *cmd;
}

Me::Renderer::Dx12::Device& Me::Renderer::Dx12::RenderLayerDx12::GetDevice()
{
	return *m_device;
}

Me::Renderer::Dx12::Context& Me::Renderer::Dx12::RenderLayerDx12::GetContext()
{
	return *m_context;
}

Me::Renderer::Dx12::Descriptor& Me::Renderer::Dx12::RenderLayerDx12::GetSRV()
{
	return *m_srv;
}

Me::Resources::Dx12::Mesh* Me::Renderer::Dx12::RenderLayerDx12::CreateMesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
	return new Me::Resources::Dx12::Mesh(a_vertices,a_indices, *m_device, GetCmd());
}

Me::Resources::Dx12::Texture* Me::Renderer::Dx12::RenderLayerDx12::LoadTexture(std::string a_path)
{
	auto tData = m_textureLoader->LoadTexture(a_path);

	auto texture = new Resources::Dx12::Texture(tData->m_srvId, *tData->m_textureData, tData->m_size);

	return texture;
}

Me::Resources::Dx12::Texture* Me::Renderer::Dx12::RenderLayerDx12::LoadTexture(const std::vector<unsigned char> a_texture, int a_width, int a_height)
{
	auto tData = m_textureLoader->LoadTexture(a_texture, a_width, a_height);

	auto texture = new Resources::Dx12::Texture(tData->m_srvId, *tData->m_textureData, tData->m_size);

	return texture;
}