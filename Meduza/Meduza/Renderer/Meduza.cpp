#include "pch/pch.h"
#include "Meduza.h"

#include "../Gfx/DirectX/Dx12_RenderLayer.h"

#include <iostream>

Meduza* Meduza::m_instance = nullptr;

Meduza::Meduza(GfxAPI a_API)
{
	printf("Meduza is a Rendering project made by Nick Wagter\n");
	m_instance = this;
	m_api = a_API;
	Initilize();
}

Meduza::~Meduza()
{
}

void Meduza::Update(float a_dt)
{
	if (m_instance->m_renderLayer == nullptr || !m_instance->m_renderLayer->IsWindowActive()) {
		m_instance->m_RendererActive = false;
		return;
	}
	m_instance->m_renderLayer->Update(a_dt);
}

void Meduza::Frame()
{
	if (m_instance->m_renderLayer == nullptr) {
		m_instance->m_RendererActive = false;
		return;
	}

	m_instance->m_renderLayer->Frame();
}

void Meduza::Clear(Colour a_colour)
{

	Colour c = a_colour;

	if (m_instance->m_renderLayer == nullptr) {
		m_instance->m_RendererActive = false;
		return;
	}


	m_instance->m_renderLayer->Clear(c);
}

void Meduza::Draw(Drawable a_drawable)
{
	m_instance->m_renderLayer->Draw(a_drawable);
}

void Meduza::ChangeAPI(GfxAPI a_newAPI)
{
	m_instance->m_api = a_newAPI;
	m_instance->m_renderLayer->DestroyLayer();
	m_instance->Initilize();
}

void Meduza::Destroy()
{
	delete m_instance;
}

bool Meduza::IsActive()
{
	return m_instance->m_RendererActive;
}

void Meduza::Initilize()
{
	m_RendererActive = true;

	switch (m_api)
	{
	case GfxAPI::DirectX12:
		printf("Gfx API DirectX12 \n");
		m_renderLayer = new Dx12_RenderLayer(720,480,"Meduza DX12");
		break;
	case GfxAPI::Vulkan:
		printf("Gfx API Vulkan \n");
		m_renderLayer = nullptr;
		break;
	}
}