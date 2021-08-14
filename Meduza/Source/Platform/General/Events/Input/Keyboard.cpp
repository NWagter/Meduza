#include "MePCH.h"
#include "Platform/General/Events/Input/Keyboard.h"

Me::Event::Input::Keyboard::Keyboard()
{

}
Me::Event::Input::Keyboard::~Keyboard()
{
    Clear();
}

Me::Event::KeyState Me::Event::Input::Keyboard::State(KeyCode a_key)
{
    auto key = m_keyboardRegister.find(a_key);
    
    if(key != m_keyboardRegister.end())
    {
        return key->second;
    }

    return KeyState::KeyUp;
}

void Me::Event::Input::Keyboard::Clear()
{
    m_keyboardRegister.clear();
}
void Me::Event::Input::Keyboard::SetState(KeyCode a_key, KeyState a_state)
{
    auto key = m_keyboardRegister.find(a_key);

    if(key != m_keyboardRegister.end())
    {
        key->second = a_state;
        return;
    }

    m_keyboardRegister.insert(std::pair<KeyCode, KeyState>(a_key, a_state));
}