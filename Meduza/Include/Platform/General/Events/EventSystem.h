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
            static EventSystem* Create(Window* a_window);
            static void Destroy();

            static EventSystem* GetEventSystem() {return ms_eventSystem;}
            
            void ShowCursor(bool a_showCursor);

            bool KeyDown(KeyCode const& a_key);
            bool KeyUp(KeyCode const& a_key);
            bool MouseButtonDown(MouseButton const& a_button);
            bool MouseButtonUp(MouseButton const& a_button);
            bool MouseButtonPressed(MouseButton const& a_button);
            Math::Vec2 MousePosition();
            Math::Vec2 ScreenSize();
            void Clear();
        private:
            EventSystem(Window* a_window);
            ~EventSystem();
            
            void OnKeyEvent(KeyCode const& a_key, KeyState const& a_state);
            void OnMouseEvent(MouseButton const& a_button, MouseEvent const& a_event);
            void OnMouseMove(Math::Vec2 const& a_position);
            void SetMouseWorldSpace(CameraComponent const& a_camera, TransformComponent const& a_transform);

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
