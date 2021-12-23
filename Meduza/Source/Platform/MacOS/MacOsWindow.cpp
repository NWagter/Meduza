#include "MePCH.h"
#include "Platform/MacOS/MacOsWindow.h"

#include "Platform/General/ContextBase.h"


Me::MacOsWindow::MacOsWindow(int const a_w, int const a_h, const char* a_title) : Window(a_w, a_h, a_title)
{
	m_active = false;

	printf("%s \n", m_title);
}

Me::MacOsWindow::~MacOsWindow()
{
}

void Me::MacOsWindow::ActiveCursor(bool)
{
	
}

void Me::MacOsWindow::Peek()
{
}

void Me::MacOsWindow::Quit()
{
	
}
void Me::MacOsWindow::SetContext(Renderer::ContextBase* a_context)
{
	m_context = a_context;
}

void Me::MacOsWindow::SetTitle(std::string const& a_title)
{

} 