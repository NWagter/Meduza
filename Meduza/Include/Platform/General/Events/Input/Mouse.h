#pragma once

namespace Me
{
    
    struct CameraComponent;
    struct TransformComponent;

    namespace Physics
    {
        struct Ray;
    }

    namespace Event
    {
        class EventSystem;
        
        namespace Input
        {
            class Mouse
            {
                Mouse();
                ~Mouse();

                MouseEvent State(MouseButton const& a_button);
                Math::Vector2 GetPosition();
                Physics::Ray GetScreenRay();


            private:
                void Clear();
                void SetState(MouseButton const& a_button, MouseEvent const& a_event);
                void SetPosition(Math::Vector2 const& a_position);
                void SetWorldSpace(CameraComponent const& a_camera, TransformComponent const& a_transform);

                std::map<MouseButton, MouseEvent> m_mouse;
                Math::Vector2 m_position;
                Physics::Ray* m_screenRay;

            friend EventSystem;
            };
        }
    }
}
