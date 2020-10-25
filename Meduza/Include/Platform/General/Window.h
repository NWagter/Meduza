#pragma once
namespace Me
{
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
			
		inline bool IsActive() { return m_active; }

	protected:
		Renderer::ContextBase* m_context;
		int m_width, m_height;
		const char* m_title;

		bool m_active;
	};
}