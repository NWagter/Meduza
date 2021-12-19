#include "MePCH.h"
#include "Utils/Timer.h"

#include "Core/Application.h"
#include "Core/Meduza.h"

#include "ECS/EntityManager.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

Me::Application::Application(int a_w,int a_h, int a_api)
{
    m_meduza = new Meduza(a_w,a_h, static_cast<GFX_API>(a_api));
}

Me::Application::~Application()
{
    delete m_meduza;
}

void Me::Application::OnUpdate(float a_dt)
{
    OnUpdate(a_dt);
}

bool Me::Application::Run()
{

    OnInitilized();

    Timer<float> deltaTimer;
    float totalTime = 0.f;
    unsigned frameCount = 0;
    float fps = 0;

    while(m_meduza->IsRunning())
    {
        ME_PROFILE_FRAME("MainThread");
        const float deltaSecond = deltaTimer.GetElapsedTime();
        m_meduza->Clear();
        
        m_meduza->Update(deltaSecond);
        Application::OnUpdate(deltaSecond);

        m_meduza->Present();

        totalTime += deltaSecond;
        frameCount++;
        if (totalTime >= 1.f)
        {
            fps = float(frameCount) / totalTime;
            frameCount = 0;
            totalTime = 0.f;
            ME_LOG("FPS : %f \n", fps);
        }
    };

    OnClose();

    return true;
}

void Me::Application::SetName(std::string a_name)
{
    m_meduza->SetAppName(a_name);
}

Me::Math::Vec2 Me::Application::GetScreenSize()
{
    return m_meduza->GetScreenSize();
}