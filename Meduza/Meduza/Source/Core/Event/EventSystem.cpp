#include "mePch.h"

#include "Core.h"
#include "Util/MeduzaHelper.h"
#include "Event/EventSystem.h"

meduza::EventSystem* meduza::EventSystem::ms_instance = nullptr;

meduza::EventSystem::EventSystem()
{
	if (ms_instance != nullptr)
	{
		return;
	}

	ms_instance = this;
}

meduza::EventSystem::~EventSystem()
{
	Flush();
}

bool meduza::EventSystem::Empty()
{
	if (m_events.size() > 0)
	{
		return false;
	}

	return true;
}

void meduza::EventSystem::AddEvent(events::Event a_event)
{
	m_events[a_event] = true;
}

void meduza::EventSystem::Flush()
{
	m_events.clear();
}

bool meduza::EventSystem::IsKeyDown(unsigned char a_keyCode)
{
	return m_keyStates[a_keyCode];
}

bool meduza::EventSystem::GetEvent(events::Event a_type)
{	
	if (m_events[a_type])
	{
		m_events.erase(a_type);
		return true;
	}

	return false;
}

bool meduza::EventSystem::OnKeyChange(char a_keyCode, bool a_isPressed)
{
	if (MeduzaHelper::ms_minimized)
		return;

	if (IsKeyDown(a_keyCode) == a_isPressed && !m_autoRepeat)
	{
		return false;
	}
	m_keyStates[a_keyCode] = a_isPressed;
	return true;
}
