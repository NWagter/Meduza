#include "mePch.h"

#include "Event/EventSystem.h"

meduza::EventSystem* meduza::EventSystem::ms_instance = nullptr;

meduza::EventSystem::EventSystem()
{
	if (ms_instance != nullptr)
	{
		return;
	}

	ms_instance = this;
	Flush();
}

meduza::EventSystem::~EventSystem()
{
	Flush();
}

void meduza::EventSystem::AddEvent(events::Event a_event)
{
	m_eventQueue.push(a_event);
}

void meduza::EventSystem::Flush()
{
	m_eventQueue = std::queue<events::Event>();
}

meduza::events::Event meduza::EventSystem::GetEvent()
{	
	if (m_eventQueue.size() > 0u) {
		auto e = m_eventQueue.front();
		m_eventQueue.pop();
		return e;
	}
	else {
		return events::Event();
	}

}
