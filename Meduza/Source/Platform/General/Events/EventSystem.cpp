#include "MePCH.h"
#include "Platform/General/Events/EventSystem.h"
#include "Platform/General/Window.h"

#include "Platform/General/Events/Input/Mouse.h"

Me::Event::EventSystem* Me::Event::EventSystem::ms_eventSystem = nullptr;

Me::Event::EventSystem* Me::Event::EventSystem::Create(Window* a_window)
{
    if(ms_eventSystem != nullptr)
    {
        ME_CORE_ASSERT_M(true, "There already is a Input System");
    }

    ms_eventSystem = new EventSystem(a_window);
    return ms_eventSystem;
}

void Me::Event::EventSystem::Destroy()
{
    if(ms_eventSystem != nullptr)
    {
        delete ms_eventSystem;
    }
}

Me::Event::EventSystem::EventSystem(Window* a_window)
{
    a_window->SetEventSystem(this);
    m_mouse = new Input::Mouse();
}

Me::Event::EventSystem::~EventSystem()
{
    delete m_mouse;
}

void Me::Event::EventSystem::Clear()
{
    m_mouse->Clear();
}

// User Check

bool Me::Event::EventSystem::KeyDown(KeyCode)
{
    return false;
}
bool Me::Event::EventSystem::KeyUp(KeyCode)
{
    return false;
}
bool Me::Event::EventSystem::MouseButtonDown(MouseButton a_button)
{    
    if(m_mouse->State(a_button) == MouseEvent::MouseDown)
    {
        return true;
    }
    return false;
}
bool Me::Event::EventSystem::MouseButtonUp(MouseButton a_button)
{     
    if(m_mouse->State(a_button) == MouseEvent::MouseUp)
    {
        return true;
    }
    return false;
}

bool Me::Event::EventSystem::MouseButtonPressed(MouseButton a_button)
{     
    if(m_mouse->State(a_button) == MouseEvent::Pressed)
    {
        return true;
    }
    return false;
}

Me::Math::Vec2 Me::Event::EventSystem::MousePosition()
{
    return Math::Vec2();
}

// Engine Set

void Me::Event::EventSystem::OnKeyEvent(KeyCode, KeyState)
{

}
void Me::Event::EventSystem::OnMouseEvent(MouseButton a_button, MouseEvent a_event)
{
    m_mouse->SetState(a_button, a_event);
}
void Me::Event::EventSystem::OnMouseMove(Math::Vec2 a_pos)
{
    m_mouse->SetPosition(a_pos);
}