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
		Window(int const a_width, int const a_height, const char* a_title);
		virtual ~Window();

		virtual void ActiveCursor(bool a_showCursor) = 0;
		virtual void Peek() = 0;
		virtual void Quit() = 0;
		virtual void SetContext(Renderer::ContextBase* a_context) = 0;
		
		virtual void SetTitle(std::string const& a_title) = 0;
		
		inline bool IsActive() { return m_active; }
		inline Math::Vector2 GetSize() { return m_size; }
		inline Math::Vector2 GetHalfSize() { return m_halfSize; }

	private:
		void SetEventSystem(Event::EventSystem* a_eventSystem);
	protected:
		void OnResize(int const a_w, int const a_h);

		Renderer::ContextBase* m_context;
		Math::Vector2 m_size;
		Math::Vector2 m_halfSize;
		const char* m_title;

		bool m_active;
		Event::EventSystem* m_eventSystem;

	friend Event::EventSystem;
	friend Renderer::ContextBase;
	};
}