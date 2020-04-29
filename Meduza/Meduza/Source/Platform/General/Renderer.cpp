#include "mePch.h"

#include "Core.h"

#include "Util/MeduzaHelper.h"
#include "Platform/General/Renderer.h"

#ifdef WINDOWS

#include "Platform/Windows/WinWindow.h"
#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Gfx/Dx12/RendererDx12.h"
#include "Platform/General/Context.h"
#endif
 
meduza::renderer::Renderer::RendererData* meduza::renderer::Renderer::CreateRenderer(math::Vec2 a_size)
{
	RendererData* returnData = new RendererData();

	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS
		returnData->window = new WinWindow(a_size);
		returnData->window->CreateContext();

		returnData->renderer = new RendererGL(*returnData->window->GetContext());

		return returnData;
#elif LINUX // WIN

#endif	
		break;

#ifdef WINDOWS
	case meduza::API::DirectX12:
		returnData->window = new WinWindow(a_size);
		returnData->window->CreateContext();
		returnData->renderer = new RendererDx12(*returnData->window->GetContext());

		return returnData;
	break;
#endif
	
#ifdef LINUX
	case meduza::API::ES2:
		printf("No ES2 defined! windows would be %f - %f \n", a_size.m_x, a_size.m_y);
	break;
#endif

	}

	return nullptr;
}
