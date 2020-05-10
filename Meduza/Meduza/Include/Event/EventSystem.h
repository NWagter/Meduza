#pragma once

#include "Event/Events.h"

#include <bitset>

namespace meduza
{
	class Keyboard;

	class EventSystem
	{
	public:
		EventSystem();
		~EventSystem();

		static EventSystem* GetEventSystem() { return ms_instance; }

		bool Empty();

		void AddEvent(events::Event);
		void Flush();

		bool IsKeyDown(unsigned char);
		bool IsKeyUp(unsigned char);

		bool GetEvent(events::Event);

		bool OnKeyChange(char, bool);
		bool m_autoRepeat = true;

	private:

		std::bitset<256> m_keyStates;
		std::unordered_map<events::Event, bool> m_events;

		static EventSystem* ms_instance;

	};
}