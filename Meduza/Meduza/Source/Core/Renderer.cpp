#include "mePch.h"

#include "Core/Renderer.h"
#ifdef PLATFORM_WINDOWS

#include "Gfx/OpenGL/RendererOpenGL.h"
#include "Gfx/DirectX12/RendererDX12.h"

#endif // PLATFORM_WINDOWS


meduza::renderer::Renderer* meduza::renderer::Renderer::CreateRenderer(API a_api, Window& a_window)
{
	switch (a_api)
	{
	case meduza::API::OpenGL:

#ifdef PLATFORM_WINDOWS

		return new RendererOpenGL(a_window);

#else // PLATFORM_WINDOWS

		printf("No OpenGL Api available \n");
		break;
#endif

	case meduza::API::DirectX12:
#ifdef PLATFORM_WINDOWS

		return new RendererDX12(a_window);

#else // PLATFORM_WINDOWS

		printf("No DX12 Api available \n");
		break;
#endif
	}

	return nullptr;
}

