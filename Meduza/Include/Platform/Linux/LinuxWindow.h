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
		LinuxWindow(int, int, const char*);
		virtual ~LinuxWindow();

		void ActiveCursor(bool) override;
		void Peek() override;
		void Quit() override;
		void SetContext(Renderer::ContextBase*) override;

		void SetTitle(std::string) override; 
		private:
		WindowData* m_windowData;
	};
}