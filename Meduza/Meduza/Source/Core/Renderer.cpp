#include "mePch.h"

#include "Core/Renderer.h"

meduza::renderer::Renderer* meduza::renderer::Renderer::CreateRenderer(API a_api)
{
	switch (a_api)
	{
	case meduza::API::OpenGL:
		break;
	case meduza::API::DirectX12:
		break;
	}

	return nullptr;
}
