#include "mePch.h"

#include "Core/Renderer.h"

#ifdef PLATFORM_WINDOWS

#include "Gfx/OpenGL/RendererOpenGL.h"

#endif // PLATFORM_WINDOWS


meduza::renderer::Renderer* meduza::renderer::Renderer::CreateRenderer(API a_api)
{
	switch (a_api)
	{
	case meduza::API::OpenGL:

#ifdef PLATFORM_WINDOWS
		return new RendererOpenGL();
#endif // PLATFORM_WINDOWS

		break;
	case meduza::API::DirectX12:
		break;
	}

	return nullptr;
}
