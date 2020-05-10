#include "mePch.h"

#include "Platform/General/Gfx/ImGuiRenderer.h"

#ifdef WINDOWS
#include "Platform/Windows/Utils/MeduzaHelper.h"
#include "Platform/Windows/Gfx/Dx12/ImGuiRendererDx12.h"
#include "Platform/Windows/Gfx/OpenGL/ImGuiRendererGL.h"
#endif

meduza::ImGuiRenderer* meduza::ImGuiRenderer::CreateRenderer(renderer::Renderer& a_renderer)
{

	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS
		return new ImGuiRendererGL(a_renderer);
#endif
		break;


#ifdef WINDOWS
	case meduza::API::DirectX12:
		return new ImGuiRendererDx12(a_renderer);
		break;
#endif

	default:
		break;
	}

	return nullptr;
}
