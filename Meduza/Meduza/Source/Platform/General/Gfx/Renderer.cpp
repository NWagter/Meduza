#include "mePch.h"

#include "Core.h"

#include "Platform/General/Gfx/Renderer.h"

#ifdef WINDOWS
#include "Platform/General/Utils/MeduzaHelper.h"
#include "Platform/Windows/Window/WinWindow.h"
#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/General/Window/Context.h"
#endif
 
meduza::renderer::Renderer::RendererData* meduza::renderer::Renderer::CreateRenderer(math::Vec2 a_size, meduza::Window* a_window)
{
	RendererData* returnData = new RendererData();

	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS
		if (a_window == nullptr)
		{
			returnData->window = new WinWindow(a_size);
		}
		else
		{
			returnData->window = a_window;
		}

		returnData->window->CreateContext();
		returnData->renderer = new RendererGL(*returnData->window->GetContext());

		return returnData;
#elif LINUX // WIN

#endif	
		break;

#ifdef WINDOWS
	case meduza::API::DirectX12:
		if (a_window == nullptr)
		{
			returnData->window = new WinWindow(a_size);
		}
		else
		{
			returnData->window = a_window;
		}

		returnData->window->CreateContext();
		returnData->renderer = new RendererDx12(*returnData->window->GetContext());

		return returnData;
	break;
#endif
	
#ifdef LINUX
	case meduza::API::ES2:
		
		
		ME_GFX_LOG("No ES2 defined! windows would be %f - %f \n", a_size.m_x, a_size.m_y);
	break;
#endif

	}
	return nullptr;
}

meduza::renderer::Renderer* meduza::renderer::Renderer::SwitchAPI(Window& a_window)
{
	Renderer* newRenderer = nullptr;
	auto window = &a_window;

	window->CreateContext();

	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS
		newRenderer = new RendererGL(*a_window.GetContext());

		return newRenderer;
#elif LINUX // WIN

#endif	
		break;

#ifdef WINDOWS
	case meduza::API::DirectX12:
		newRenderer = new RendererDx12(*a_window.GetContext());

		return newRenderer;
		break;
#endif

#ifdef LINUX
	case meduza::API::ES2:


		ME_GFX_LOG("No ES2 defined! windows would be %f - %f \n", a_size.m_x, a_size.m_y);
		break;
#endif

	}
	return newRenderer;
}
