#include "mePch.h"

#include "Platform/Windows/DX12_RenderLayer.h"
#include "Platform/Windows/WinWindow.h"
#include "..\..\..\Include\Platform\Windows\DX12_RenderLayer.h"

mr::DX12_Renderlayer::DX12_Renderlayer(Window& a_window)
{
	m_window = &a_window;
}

void mr::DX12_Renderlayer::Clear(float[4])
{
}

void mr::DX12_Renderlayer::Update()
{
}

void mr::DX12_Renderlayer::Render()
{
}
