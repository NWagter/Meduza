#pragma once

#include "Platform/General/Events/Events.h"

namespace Me
{
    class Window;
    class WindowsWindow;
    class LinuxWindow;
    class MousePickingSystem;

    struct CameraComponent;
    struct TransformComponent;

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
            
            void ShowCursor(bool);

            bool KeyDown(KeyCode);
            bool KeyUp(KeyCode);
            bool MouseButtonDown(MouseButton);
            bool MouseButtonUp(MouseButton);
            bool MouseButtonPressed(MouseButton);
            Math::Vec2 MousePosition();
            Math::Vec2 ScreenSize();
            void Clear();
        private:
            EventSystem(Window*);
            ~EventSystem();
            
            void OnKeyEvent(KeyCode, KeyState);
            void OnMouseEvent(MouseButton, MouseEvent);
            void OnMouseMove(Math::Vec2);
            void SetMouseWorldSpace(CameraComponent, TransformComponent);

            static EventSystem* ms_eventSystem;

            Input::Mouse* m_mouse;
            Input::Keyboard* m_keyboard;

            Me::Math::Vec2 m_screenSize;
            Window* m_window;

        friend Window;
        friend WindowsWindow;
        friend LinuxWindow;
        friend MousePickingSystem;
        };

    }    
}
