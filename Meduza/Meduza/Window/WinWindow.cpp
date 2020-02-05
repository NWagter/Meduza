#include "pch/pch.h"
#include "WinWindow.h"

#include "imgui.h"
#include "imgui_impl_win32.h"


WinWindow::WinWindow(int a_width, int a_height, const char* a_title) : Window(a_width, a_height, a_title)
{
	RECT wr;
	wr.left = 100;
	wr.right = a_width + wr.left;
	wr.top = 100;
	wr.bottom = a_height + wr.top;

	m_hwnd = CreateWindow(WindowClass::GetName(), a_title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	m_windowIsActive = true;
}

WinWindow::~WinWindow()
{
	DestroyWindow(m_hwnd);	
}

void WinWindow::SetTitle(const std::string a_newTitle)
{
	Window::SetTitle(a_newTitle);

	SetWindowText(m_hwnd, a_newTitle.c_str());

}

bool WinWindow::PeekMsg()
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			m_windowIsActive = false;
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return true;
}

const HWND WinWindow::GetWindowHandle()
{
	return m_hwnd;
}

LRESULT __stdcall WinWindow::HandleMsgSetup(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	//use the create parameter in createWindow to store window class pointer at WinApi!
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

LRESULT __stdcall WinWindow::HandleMsgThunk(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	WinWindow* const pWnd = reinterpret_cast<WinWindow*>(GetWindowLongPtr(a_hWnd, GWLP_USERDATA));

	//Handle the messages!
	return pWnd->HandleMsg(a_hWnd, a_msg, a_wParam, a_lParam);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WinWindow::HandleMsg(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(a_hWnd, a_msg, a_wParam, a_lParam))
		return true;

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

const char* WinWindow::WindowClass::GetName()
{
	return ms_wndClassName;
}

HINSTANCE WinWindow::WindowClass::GetInstance()
{
	return ms_windowClass.m_hInstance;
}


WinWindow::WindowClass WinWindow::WindowClass::ms_windowClass;

WinWindow::WindowClass::WindowClass() :
	m_hInstance(GetModuleHandle(0))
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

WinWindow::WindowClass::~WindowClass()
{
	UnregisterClass(ms_wndClassName, GetInstance());
}
