#include "MePCH.h"
#include "Platform/General/Events/Input/Mouse.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"

Me::Event::Input::Mouse::Mouse()
{
    m_mouse.insert(std::make_pair<MouseButton, MouseEvent>(MouseButton::LButton, MouseEvent::MouseUp));
    m_mouse.insert(std::make_pair<MouseButton, MouseEvent>(MouseButton::RButton, MouseEvent::MouseUp));
    m_mouse.insert(std::make_pair<MouseButton, MouseEvent>(MouseButton::MButton, MouseEvent::MouseUp));

    m_screenRay = new Physics::Ray();
}

Me::Event::Input::Mouse::~Mouse()
{
    m_mouse.clear();
    delete m_screenRay;
}

void Me::Event::Input::Mouse::Clear()
{
    for(auto mB : m_mouse)
    {
        SetState(mB.first, mB.second);
    }
}

Me::Event::MouseEvent Me::Event::Input::Mouse::State(MouseButton const& a_button)
{
    auto mEvent = m_mouse.find(a_button);
    return mEvent->second;
}

Me::Math::Vector2 Me::Event::Input::Mouse::GetScreenPosition()
{
    return m_position;
}

Me::Math::Vector2 Me::Event::Input::Mouse::GetWorldPosition()
{
    return m_worldPosition;
}

Me::Physics::Ray Me::Event::Input::Mouse::GetScreenRay()
{
    return *m_screenRay;
}

void Me::Event::Input::Mouse::SetState(MouseButton const& a_button, MouseEvent const& a_event)
{    
    auto mEvent = m_mouse.find(a_button);

    if(a_event == MouseEvent::MouseDown && 
        (mEvent->second == MouseEvent::MouseDown || mEvent->second == MouseEvent::Pressed))
    {
        mEvent->second = MouseEvent::Pressed;
        return;
    }

    if(mEvent->second != a_event)
    {
        mEvent->second = a_event;
    }
}

void Me::Event::Input::Mouse::SetPosition(Math::Vector2 const& a_position)
{
    m_position = a_position;
}

void Me::Event::Input::Mouse::AddScrollDelta(float const i_scrollDelta)
{
    float const minScroll = -50.0f;
    float const maxScroll = 50.0f;

    m_scrollDelta = Math::Clamp(minScroll, maxScroll, m_scrollDelta + i_scrollDelta);
}

void Me::Event::Input::Mouse::SetWorldSpace(CameraComponent const& a_camera, TransformComponent const& a_transform)
{

}