#pragma once

#include "Platform/General/Events/Events.h"

namespace Me
{
    class Window;
    class WindowsWindow;

    namespace Event
    {
        namespace Input
        {
            class Mouse;
            class Keyboard;
        }

        class EventSystem
        {
        public:
            static EventSystem* Create(Window*);
            static void Destroy();

            static EventSystem* GetEventSystem() {return ms_eventSystem;}
            
            bool KeyDown(KeyCode);
            bool KeyUp(KeyCode);
            bool MouseButtonDown(MouseButton);
            bool MouseButtonUp(MouseButton);
            bool MouseButtonPressed(MouseButton);
            Math::Vec2 MousePosition();

            void Clear();
        private:
            EventSystem(Window*);
            ~EventSystem();
            
            void OnKeyEvent(KeyCode, KeyState);
            void OnMouseEvent(MouseButton, MouseEvent);
            void OnMouseMove(Math::Vec2);

            static EventSystem* ms_eventSystem;

            Input::Mouse* m_mouse;
            Input::Keyboard* m_keyboard;

        friend Window;
        friend WindowsWindow;
        };

    }    
}
