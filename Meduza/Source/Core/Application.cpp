#include "MePCH.h"
#include "Utils/Timer.h"

#include "Core/Application.h"
#include "Core/Meduza.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#include "ECS/EntityManager.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

Me::Application::Application(int a_w,int a_h)
{
    m_meduza = new Meduza(a_w,a_h);
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

    float fps;

    while(m_meduza->IsRunning())
    {
        const float deltaSeconds = deltaTimer.GetElapsedTime();
        m_meduza->Clear();
        m_meduza->Update(deltaSeconds);
        Application::OnUpdate(deltaSeconds);

        m_meduza->Present();

        totalTime += deltaSeconds;
        frameCount++;
        if (totalTime >= 1.f)
        {
            fps = float(frameCount) / totalTime;
            frameCount = 0;
            totalTime = 0.f;
            ME_CORE_LOG("FPS : %f \n", fps);
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