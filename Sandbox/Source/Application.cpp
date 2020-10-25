#include "PCH.h"
#include "Application.h"
#include "Core/Meduza.h"

Application::Application()
{
    m_meduza = new Me::Meduza();
}

Application::~Application()
{

}

void Application::Run()
{
    while(m_meduza->IsRunning())
    {
        m_meduza->Clear();

        m_meduza->Update();

        m_meduza->Present();
    }
}

void Application::Destroy()
{
    delete m_meduza;
}