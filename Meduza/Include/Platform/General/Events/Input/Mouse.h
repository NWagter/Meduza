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
                Math::Vector2 GetScreenPosition();
                Math::Vector2 GetWorldPosition();
                Physics::Ray GetScreenRay();


            private:
                void Clear();
                void SetState(MouseButton const& a_button, MouseEvent const& a_event);
                void SetPosition(Math::Vector2 const& a_position);
                void AddScrollDelta(float const i_scrollDelta);
                void SetWorldSpace(CameraComponent const& a_camera, TransformComponent const& a_transform);

                std::map<MouseButton, MouseEvent> m_mouse;
                Math::Vector2 m_position;
                Math::Vector2 m_worldPosition;
                Physics::Ray* m_screenRay;

                float m_scrollDelta = 0.0f;

            friend EventSystem;
            };
        }
    }
}
