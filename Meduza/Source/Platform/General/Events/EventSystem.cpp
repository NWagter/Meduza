#include "MePCH.h"
#include "Platform/General/Events/EventSystem.h"
#include "Platform/General/Window.h"

#include "Platform/General/Events/Input/Mouse.h"
#include "Platform/General/Events/Input/Keyboard.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

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
    m_window = a_window;
    m_mouse = new Input::Mouse();
    m_keyboard = new Input::Keyboard();
}

Me::Event::EventSystem::~EventSystem()
{
    delete m_mouse;
    delete m_keyboard;
}

void Me::Event::EventSystem::ShowCursor(bool a_show)
{
    m_window->ActiveCursor(a_show);
}

void Me::Event::EventSystem::Clear()
{
    m_mouse->Clear();
    m_keyboard->Clear();
}

// User Check

bool Me::Event::EventSystem::KeyDown(KeyCode const& a_key)
{
    char upperKey = toupper(char(a_key));    
    char lowerKey = tolower(char(a_key));    

    if(m_keyboard->State(KeyCode(upperKey)) == KeyState::KeyDown || m_keyboard->State(KeyCode(lowerKey)) == KeyState::KeyDown)
    {
        return true;
    }

    return false;
}
bool Me::Event::EventSystem::KeyUp(KeyCode const& a_key)
{
    char upperKey = toupper(char(a_key));    
    char lowerKey = tolower(char(a_key));    

    if(m_keyboard->State(KeyCode(upperKey)) == KeyState::KeyUp || m_keyboard->State(KeyCode(lowerKey)) == KeyState::KeyUp)
    {
        return true;
    }
    
    return false;
}
bool Me::Event::EventSystem::MouseButtonDown(MouseButton const& a_button)
{    
    if(m_mouse->State(a_button) == MouseEvent::MouseDown)
    {
        return true;
    }
    return false;
}
bool Me::Event::EventSystem::MouseButtonUp(MouseButton const& a_button)
{     
    if(m_mouse->State(a_button) == MouseEvent::MouseUp)
    {
        return true;
    }
    return false;
}

bool Me::Event::EventSystem::MouseButtonPressed(MouseButton const& a_button)
{     
    if(m_mouse->State(a_button) == MouseEvent::Pressed)
    {
        return true;
    }
    return false;
}

float Me::Event::EventSystem::GetMouseScroll()
{
    return m_mouse->m_scrollDelta;
}

void Me::Event::EventSystem::OnKeyEvent(KeyCode const& a_key, KeyState const& a_state)
{
    m_keyboard->SetState(a_key, a_state);
}

void Me::Event::EventSystem::OnMouseEvent(MouseButton const& a_button, MouseEvent const& a_event)
{
    m_mouse->SetState(a_button, a_event);
}
void Me::Event::EventSystem::OnMouseMove(Math::Vector2 const& a_position)
{
    m_mouse->SetPosition(a_position);
}

void Me::Event::EventSystem::OnMouseScroll(bool const a_scrollUp)
{
    float const scrollWeigth = 10.0f;

    m_mouse->AddScrollDelta(a_scrollUp ? scrollWeigth : -scrollWeigth);
}