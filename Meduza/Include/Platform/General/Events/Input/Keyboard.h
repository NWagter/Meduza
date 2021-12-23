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

                KeyState State(KeyCode const& a_key);

            private:
                void Clear();
                void SetState(KeyCode const& a_key, KeyState const& a_state);
                
                std::map<KeyCode, KeyState> m_keyboardRegister;

                friend EventSystem;
            };
        }
    }
}
