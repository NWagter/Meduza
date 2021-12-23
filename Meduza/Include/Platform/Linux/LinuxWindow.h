#pragma once
#include "Platform/General/Window.h"

struct WindowData
{
	Display *m_display;
	int m_screenHandle;
	Window m_window;
	XEvent m_event;
};

namespace Me
{
	class LinuxWindow : public Window
	{
	public:
		LinuxWindow(int const a_width, int const a_height, const char* a_title);
		virtual ~LinuxWindow();

		void ActiveCursor(bool a_showCursor) override;
		void Peek() override;
		void Quit() override;
		void SetContext(Renderer::ContextBase* a_context) override;

		void SetTitle(std::string const& a_title) override; 
		private:
		
		void HandleInput();

		WindowData* m_windowData;
	};
}