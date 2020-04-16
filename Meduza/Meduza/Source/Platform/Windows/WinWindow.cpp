#include "mePch.h"

#include "Platform/Windows/WinWindow.h"

meduza::WinWindow::WinWindow(int a_width, int a_height, std::string a_title)
{
	m_title = a_title;

	RECT wr;
	wr.left = 100;
	wr.right = a_width + wr.left;
	wr.top = 100;
	wr.bottom = a_height + wr.top;

	m_windowHandle = CreateWindow(WindowClass::GetName(), a_title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
	m_windowActive = true;
	
}

meduza::WinWindow::~WinWindow()
{
	printf("%s destroy! \n  ", m_title.c_str());
}

void meduza::WinWindow::Peek()
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message == WM_QUIT)
		{
			m_windowActive = false;
			return;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
}

bool meduza::WinWindow::WindowActive()
{
	return m_windowActive;
}

void meduza::WinWindow::SetTitle(std::string a_title)
{
	m_title = a_title;

	SetWindowText(m_windowHandle, m_title.c_str());
}

LRESULT __stdcall meduza::WinWindow::HandleMsgSetup(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	if (a_msg == WM_NCCREATE)
	{
		//extract ptr to window class from creation data!
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(a_lParam);
		WinWindow* const pWnd = static_cast<WinWindow*>(pCreate->lpCreateParams);
		//Set WinAPI-managed user data to store window class ptr
		SetWindowLongPtr(a_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//Set Message proc to normal handler in stead of the setup one!
		SetWindowLongPtr(a_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WinWindow::HandleMsgThunk));
		// forward message to window class handler
		return pWnd->HandleMsg(a_hWnd, a_msg, a_wParam, a_lParam);
	}
	return DefWindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
}

LRESULT __stdcall meduza::WinWindow::HandleMsgThunk(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	WinWindow* const pWnd = reinterpret_cast<WinWindow*>(GetWindowLongPtr(a_hWnd, GWLP_USERDATA));

	//Handle the messages!
	return pWnd->HandleMsg(a_hWnd, a_msg, a_wParam, a_lParam);
}

LRESULT meduza::WinWindow::HandleMsg(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	switch (a_msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
}

meduza::WinWindow::WindowClass meduza::WinWindow::WindowClass::ms_windowClass;

meduza::WinWindow::WindowClass::WindowClass() : m_hInstance(nullptr)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	//Load image from resources
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	//Load image from resources
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}

meduza::WinWindow::WindowClass::~WindowClass()
{
	UnregisterClass(ms_wndClassName, GetInstance());
}
