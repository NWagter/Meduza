#include "MePCH.h"
#include "Platform/General/Events/Input/Mouse.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

Me::Event::Input::Mouse::Mouse()
{
    m_mouse.insert(std::make_pair<MouseButton, MouseEvent>(MouseButton::LButton, MouseEvent::MouseUp));
    m_mouse.insert(std::make_pair<MouseButton, MouseEvent>(MouseButton::RButton, MouseEvent::MouseUp));
    m_mouse.insert(std::make_pair<MouseButton, MouseEvent>(MouseButton::MButton, MouseEvent::MouseUp));
}

Me::Event::Input::Mouse::~Mouse()
{
    m_mouse.clear();
}

void Me::Event::Input::Mouse::Clear()
{
    for(auto mB : m_mouse)
    {
        SetState(mB.first, mB.second);
    }
}

Me::Event::MouseEvent Me::Event::Input::Mouse::State(MouseButton a_button)
{
    auto mEvent = m_mouse.find(a_button);
    return mEvent->second;
}

Me::Math::Vec2 Me::Event::Input::Mouse::GetPosition()
{
    return m_position;
}

void Me::Event::Input::Mouse::SetState(MouseButton a_button, MouseEvent a_event)
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

void Me::Event::Input::Mouse::SetPosition(Math::Vec2 a_pos)
{
    m_position = a_pos;
}

void Me::Event::Input::Mouse::SetWorldSpace(CameraComponent a_camera, TransformComponent a_trans)
{
    float x = (m_position.m_x * 2) / a_camera.m_size.m_x;
    float y = (m_position.m_y * 2) / a_camera.m_size.m_y;
}