#include "mePch.h"

#include "Util/MeduzaHelper.h"
#include "Platform/General/ImGuiRenderer.h"

#ifdef WINDOWS

#endif

meduza::ImGuiRenderer* meduza::ImGuiRenderer::CreateRenderer(renderer::Renderer&)
{

	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
#ifdef WINDOWS

#endif
		break;


#ifdef WINDOWS
	case meduza::API::DirectX12:

		break;
#endif

	default:
		break;
	}

	return nullptr;
}
