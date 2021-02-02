#pragma once

namespace Me
{
    namespace Event
    {
        class EventSystem;

        namespace Input
        {
            class Keyboard
            {
                Keyboard();
                ~Keyboard();

                KeyState State(KeyCode);

            private:
                void Clear();
                void SetState(KeyCode, KeyState);
                
                std::map<KeyCode, KeyState> m_keyboardRegister;

                friend EventSystem;
            };
        }
    }
}
