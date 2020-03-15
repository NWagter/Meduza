#include "mePch.h"

#include "Platform\Windows\WinWindow.h"

mr::WinWindow::WinWindow(int a_width, int a_height, std::string a_title)
{
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
	m_isActive = true;

	m_isActive = true;
}

mr::WinWindow::~WinWindow()
{
	DestroyWindow(m_windowHandle);
}

void mr::WinWindow::SetTitle(const std::string a_title)
{
	SetWindowText(m_windowHandle, a_title.c_str());
}

bool mr::WinWindow::Peek()
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message == WM_QUIT)
		{
			m_isActive = false;
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return true;
}

void mr::WinWindow::Resize()
{
}

LRESULT __stdcall mr::WinWindow::HandleMsgSetup(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
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

LRESULT __stdcall mr::WinWindow::HandleMsgThunk(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	WinWindow* const pWnd = reinterpret_cast<WinWindow*>(GetWindowLongPtr(a_hWnd, GWLP_USERDATA));

	//Handle the messages!
	return pWnd->HandleMsg(a_hWnd, a_msg, a_wParam, a_lParam);
}


LRESULT mr::WinWindow::HandleMsg(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	switch(a_msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
}

const char* mr::WinWindow::WindowClass::GetName()
{
	return ms_wndClassName;
}

mr::WinWindow::WindowClass mr::WinWindow::WindowClass::ms_windowClass;

HINSTANCE mr::WinWindow::WindowClass::GetInstance()
{
	return  ms_windowClass.m_hInstance;
}

mr::WinWindow::WindowClass::WindowClass()
	: m_hInstance(nullptr)
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

mr::WinWindow::WindowClass::~WindowClass()
{
	UnregisterClass(ms_wndClassName, GetInstance());
}
