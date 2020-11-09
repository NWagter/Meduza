#include "MePCH.h"
#include "Core/Meduza.h"

#include "ECS/EntityManager.h"
#include "ECS/Entity.h"
#include "Core/Systems/RenderSystem.h"

#include "Core/Components/TransformComponent.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#elif PLATFORM_APPLE
#include "Platform/MacOS/MacOsWindow.h"
#endif


Me::Meduza::Meduza()
{
	m_isRunning = true;

#ifdef PLATFORM_WINDOWS
	m_window = new WindowsWindow(720, 680, "Meduza | Windows");
#elif PLATFORM_LINUX
	m_window = new LinuxWindow(720, 680, "Meduza | Linux");
#elif PLATFORM_APPLE
	m_window = new MacOsWindow(720, 680, "Meduza | Apple");
#endif

	if(m_window != nullptr)
	{
		m_renderLayer = Renderer::RenderLayer::CreateRenderer(m_window);

		if(m_renderLayer == nullptr)
		{			
			ME_CORE_ASSERT_M(false, "No Renderer Available!");
			m_window->Quit();
		}
	}

	Resources::MeshLibrary::CreateMeshLibrary(*m_renderLayer);
	Resources::ShaderLibrary::CreateShaderLibrary(*m_renderLayer);
	Resources::TextureLibrary::CreateTextureLibrary(*m_renderLayer);
	EntityManager::CreateEntityManager();

	auto r = new RenderSystem();
	auto e1 = EntityManager::CreateEntity();
	auto e2 = EntityManager::CreateEntity();

	EntityManager::AddComponent(e1, new TransformComponent());
	r->AddComponentToFilter(TransformComponent::m_componentID);


}

Me::Meduza::~Meduza()
{
	Destroy();
}

void Me::Meduza::Clear()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Clear(Colours::ROYAL_PURPLE);
		return;
	}

	m_isRunning = false;
}

void Me::Meduza::Update()
{
	if(m_window == nullptr)
	{
		m_isRunning = false;
		return;
	}
	
	m_window->Peek();
	EntityManager::GetEntityManager()->Update(0);
		
	if (!m_window->IsActive())
	{
		m_isRunning = false;
	}
}

void Me::Meduza::Present()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Present();
		return;
	}

	m_isRunning = false;
}

void Me::Meduza::Destroy()
{
	Resources::TextureLibrary::Destroy();
	Resources::ShaderLibrary::Destroy();
	Resources::MeshLibrary::Destroy();

	if(m_window != nullptr)
	{
		delete m_window;
	}

	if(m_renderLayer != nullptr)
	{
		delete m_renderLayer;
	}
}

void Me::Meduza::Submit(Renderable* a_renderable)
{
	m_renderLayer->Submit(*a_renderable);
}

void Me::Meduza::Submit(std::vector<Renderable*>)
{

}