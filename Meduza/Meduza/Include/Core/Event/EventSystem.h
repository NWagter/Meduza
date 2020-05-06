#pragma once

#include "MeduzaUtil.h"
#include "Event/Events.h"

namespace meduza
{

	class EventSystem
	{
	public:
		EventSystem();
		~EventSystem();

		static EventSystem* GetInstance() { return ms_instance; }

		void AddEvent(events::Event);
		void Flush();

		events::Event GetEvent();
		EventSystem* GetEventSystem() { return ms_instance; }

	private:

		static EventSystem* ms_instance;
		std::queue<events::Event> m_eventQueue;
	};
}