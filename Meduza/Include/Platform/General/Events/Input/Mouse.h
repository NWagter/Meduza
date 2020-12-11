#pragma once

namespace Me
{
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


            private:
                void Clear();
                void SetState(MouseButton, MouseEvent);
                void SetPosition(Math::Vec2);

                std::map<MouseButton, MouseEvent> m_mouse;
                Math::Vec2 m_position;

            friend EventSystem;
            };
        }
    }
}
