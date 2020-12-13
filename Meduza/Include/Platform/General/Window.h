#pragma once
namespace Me
{
	namespace Event
	{
		class EventSystem;
	}

	namespace Renderer
	{
		class ContextBase;
		class RenderLayer;
	}

	class Window 
	{
	public:
		Window(int, int, const char*);
		virtual ~Window();

		virtual void Peek() = 0;
		virtual void Quit() = 0;
		virtual void SetContext(Renderer::ContextBase*) = 0;
		
		virtual void SetTitle(std::string) = 0;
		
		inline bool IsActive() { return m_active; }
		inline Math::Vec2 GetSize() { return m_size; }

	private:
		void SetEventSystem(Event::EventSystem*);
	protected:
		Renderer::ContextBase* m_context;
		Math::Vec2 m_size;
		const char* m_title;

		bool m_active;
		Event::EventSystem* m_eventSystem;

	friend Event::EventSystem;
	};
}