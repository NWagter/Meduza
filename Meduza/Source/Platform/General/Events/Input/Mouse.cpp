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

Me::Math::Vec2 Me::Event::Input::Mouse::GetPosition()
{
    return m_position;
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

void Me::Event::Input::Mouse::SetPosition(Math::Vec2 const& a_position)
{
    m_position = a_position;
}

void Me::Event::Input::Mouse::SetWorldSpace(CameraComponent const& a_camera, TransformComponent const& a_transform)
{
    float x = (m_position.m_x * 2) / a_camera.m_size.m_x;
    float y = (m_position.m_y * 2) / a_camera.m_size.m_y;

    Math::Vec4 ray_clip = Math::Vec4(x,y, -1, 1);

    Math::Mat4 pMat = Math::Mat4::Identity();
    pMat.SetPosition(a_transform.m_translation);

    Math::Mat4 rMat = Math::Mat4::Identity();
    rMat.Rotation(a_transform.m_rotation);

    Math::Mat4 view = rMat * pMat.Inverse();

    Math::Mat4 projection = Math::GetProjectionMatrix(45.0f,
    a_camera.m_size.m_x / a_camera.m_size.m_y, a_camera.m_near, a_camera.m_far);

    Math::Vec4 rayEye = ( projection.Inverse() * ray_clip);
    rayEye = Math::Vec4(rayEye.m_x, rayEye.m_y, -1.0, 0.0);
    Math::Vec4 rayWorld = (view.Inverse() * rayEye);
    m_screenRay->m_origin = Math::Vec3(rayWorld.m_x,rayWorld.m_y,rayWorld.m_z).Normalize();

    if(m_mouse[MouseButton::RButton] == MouseEvent::MouseDown)
    {
        ME_LOG("Hello \n");
    }
}