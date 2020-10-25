#include "MePCH.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Platform/General/ContextBase.h"

Me::WindowsWindow::WindowsWindow(int a_w, int a_h, const char* a_title) : Window(a_w, a_h, a_title)
{
	m_active = true;

	ME_LOG("Window Created : %s \n", m_title);

	RECT wr;
	wr.left = 100;
	wr.right = int(m_width) + wr.left;
	wr.top = 100;
	wr.bottom = int(m_height) + wr.top;
	
	m_hWnd = CreateWindow(WindowClass::GetName(), m_title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}

Me::WindowsWindow::~WindowsWindow()
{
}

void Me::WindowsWindow::Peek()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message == WM_QUIT)
		{
			m_active = false;
			return;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Me::WindowsWindow::Quit()
{
		PostQuitMessage(0);
}

void Me::WindowsWindow::SetContext(Renderer::ContextBase* a_context)
{
	m_context = a_context;
}

LRESULT __stdcall Me::WindowsWindow::HandleMsgSetup(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{

	if (a_msg == WM_NCCREATE) {
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(a_lParam);
		WindowsWindow* const pWnd = static_cast<WindowsWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(a_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(a_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgThunk));
		return pWnd->HandleMsg(a_hwnd, a_msg, a_wParam, a_lParam);
	}
	return DefWindowProc(a_hwnd, a_msg, a_wParam, a_lParam);
}

LRESULT __stdcall Me::WindowsWindow::HandleMsgThunk(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{	//Get The window ptr stored in the API user data

	WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(a_hwnd, GWLP_USERDATA));

	//Handle the messages!
	return pWnd->HandleMsg(a_hwnd, a_msg, a_wParam, a_lParam);
}

LRESULT Me::WindowsWindow::HandleMsg(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	switch (a_msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(a_hwnd, a_msg, a_wParam, a_lParam);
}

Me::WindowsWindow::WindowClass Me::WindowsWindow::WindowClass::ms_wndClass;

Me::WindowsWindow::WindowClass::WindowClass() :
	m_hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	//Load image from resources
	wc.hIcon = nullptr;//static_cast<HICON>(LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	//Load image from resources
	wc.hIconSm = nullptr;// static_cast<HICON>(LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));

	RegisterClassEx(&wc);
}

Me::WindowsWindow::WindowClass::~WindowClass()
{
	UnregisterClass(ms_wndName, GetInstance());
}