#include "mePch.h"

#include "Platform/Cross Platform/Vulkan/VK_RenderLayer.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WinWindow.h"
#endif

mr::VK_RenderLayer::VK_RenderLayer(Window& a_window)
{
#ifdef PLATFORM_WINDOWS
	m_window = static_cast<WinWindow*>(&a_window);
#endif // PLATFORM_WINDOWS


	VkInstanceCreateInfo vkInstInfo{};
	vkInstInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	//vkCreateInstance(&vkInstInfo,);

}

mr::VK_RenderLayer::~VK_RenderLayer()
{
	
}

void mr::VK_RenderLayer::Clear(float[4])
{

}

void mr::VK_RenderLayer::PreRender()
{

}

void mr::VK_RenderLayer::Render()
{

}
