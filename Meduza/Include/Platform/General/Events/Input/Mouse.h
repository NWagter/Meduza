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

                MouseEvent State(MouseButton);
                Math::Vec2 GetPosition();
                Physics::Ray GetScreenRay();


            private:
                void Clear();
                void SetState(MouseButton, MouseEvent);
                void SetPosition(Math::Vec2);
                void SetWorldSpace(CameraComponent, TransformComponent);

                std::map<MouseButton, MouseEvent> m_mouse;
                Math::Vec2 m_position;
                Physics::Ray* m_screenRay;

            friend EventSystem;
            };
        }
    }
}
