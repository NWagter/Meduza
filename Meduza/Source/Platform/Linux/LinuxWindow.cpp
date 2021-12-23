#include "MePCH.h"
#include "Platform/Linux/LinuxWindow.h"

#include "Platform/Linux/Graphics/Context.h"

#include "Platform/General/Events/EventSystem.h"

Me::LinuxWindow::LinuxWindow(int a_w, int a_h, const char* a_title) : Window(a_w, a_h, a_title)
{

	m_windowData = new WindowData();

	m_windowData->m_display = XOpenDisplay(NULL);
	if(m_windowData->m_display == NULL)
	{
		ME_GFX_LOG("UCan't open Linux Window");
		return;
	}

	m_windowData->m_screenHandle = DefaultScreen(m_windowData->m_display);

	m_windowData->m_window = XCreateSimpleWindow(m_windowData->m_display,
									RootWindow(m_windowData->m_display, m_windowData->m_screenHandle),
									100,100, m_size.m_x,m_size.m_y, 1,
									BlackPixel(m_windowData->m_display, m_windowData->m_screenHandle),
									WhitePixel(m_windowData->m_display, m_windowData->m_screenHandle));

	XSelectInput(m_windowData->m_display, m_windowData->m_window, 
		ExposureMask | KeyPressMask | KeyReleaseMask |
		PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
		ShiftMask | StructureNotifyMask);

	XMapWindow(m_windowData->m_display, m_windowData->m_window);
	XStoreName(m_windowData->m_display, m_windowData->m_window, m_title);
	m_active = true;

}

Me::LinuxWindow::~LinuxWindow()
{
}

void Me::LinuxWindow::ActiveCursor(bool)
{

}

void Me::LinuxWindow::Peek()
{
	while(XPending(m_windowData->m_display))
	{
		XNextEvent(m_windowData->m_display, &m_windowData->m_event);
		HandleInput();
	}	
}

void Me::LinuxWindow::Quit()
{
	
}

void Me::LinuxWindow::SetTitle(std::string const& a_title)
{
	XStoreName(m_windowData->m_display, m_windowData->m_window, a_title.c_str());
} 

void Me::LinuxWindow::SetContext(Renderer::ContextBase* a_context)
{
	m_context = a_context;
	dynamic_cast<Renderer::GL::Context*>(m_context)->InitContext(*m_windowData, m_size.m_x, m_size.m_y);
}

void Me::LinuxWindow::HandleInput()
{
	int key = XLookupKeysym(&m_windowData->m_event.xkey, 0);

	if(key > 255)
	{
		key = m_windowData->m_event.xkey.keycode;
	}

	if(m_windowData->m_event.type == KeyPress)
	{
		Event::KeyCode keycode = static_cast<Event::KeyCode>(key);
		m_eventSystem->OnKeyEvent(keycode, Event::KeyState::KeyDown);
	}

	if(m_windowData->m_event.type == KeyRelease)
	{
		Event::KeyCode keycode = static_cast<Event::KeyCode>(key);
		m_eventSystem->OnKeyEvent(keycode, Event::KeyState::KeyUp);
	}
}