#pragma once

#include <string>

#include "Math/MeduzaMath.h"
#include "Event/Events.h"

namespace meduza
{
	class EventSystem;

	namespace renderer
	{
		class Context;
	}

	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void EnableImGui() = 0;

		virtual void Peek() = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetTitle(std::string) = 0;
		virtual void CreateContext() = 0;

		inline renderer::Context* GetContext() { return m_context; }

		inline math::Vec2 GetSize() { return m_size; }
		inline std::string GetTitle() { return m_title; }
		inline bool GetActive() { return m_windowActive; }

		inline void SetEventSystem(EventSystem& a_eventSystem) { m_eventSystem = &a_eventSystem; }
	protected:

		renderer::Context* m_context = nullptr;
		EventSystem* m_eventSystem = nullptr;
		math::Vec2 m_size;
		std::string m_title;
		bool m_windowActive = false;

	private:
		virtual void PushEvent(events::Event) = 0;
	};
}
