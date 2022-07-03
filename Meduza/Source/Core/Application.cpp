#include "MePCH.h"
#include "Utils/Timer.h"

#include "Core/Application.h"
#include "Core/Meduza.h"

#include "ECS/EntityManager.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Utils/MeduzaDebug.h"

Me::Application::Application(int a_w,int a_h, int a_api)
{
    m_meduza = new Meduza(a_w,a_h, static_cast<GFX_API>(a_api));
}

Me::Application::~Application()
{
    ME_PROFILE_STOP();
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

    ME_PROFILE_APP("Meduza");
    while(m_meduza->IsRunning())
    {
        ME_PROFILE_FRAME("MainThread");

        float const deltaSecond = deltaTimer.GetElapsedTime();

        float timeScale = 1.0f;
#ifdef EDITOR
        timeScale = Me::Debug::MeduzaDebug::GetDebuggingSettings().m_timeScale;
#endif // EDITOR

        float const deltaTime = deltaSecond * timeScale;
        m_meduza->Clear();
        
        m_meduza->Update(deltaTime);
        Application::OnUpdate(deltaTime);

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

void Me::Application::SetName(std::string a_appName)
{
    m_meduza->SetAppName(a_appName);
}

Me::Math::Vector2 Me::Application::GetScreenSize()
{
    return m_meduza->GetScreenSize();
}