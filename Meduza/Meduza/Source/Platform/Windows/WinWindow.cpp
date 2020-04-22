#include "mePch.h"

#include "Platform/Windows/WinWindow.h"
#include "Platform/Windows/Gfx/OpenGL/ContextGL.h"

meduza::WinWindow::WinWindow(math::Vec2 a_size, API a_api)
{
	m_windowActive = true;
	std::string title = "Meduza | Renderer | Windows";
	SetTitle(title);

	RECT wr;
	wr.left = 100;
	wr.right = int(a_size.m_x) + wr.left;
	wr.top = 100;
	wr.bottom = int(a_size.m_y) + wr.top;

	m_size = a_size;

	m_hWnd = CreateWindow(WindowClass::GetName(), title.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	
	switch (a_api)
	{
	case meduza::API::OpenGL:
		m_context = new renderer::ContextGL(m_hWnd);
		SetTitle(title + "| OpenGL");
		break;
	case meduza::API::DirectX12:
		break;
	}
}

meduza::WinWindow::~WinWindow()
{
	DestroyWindow(m_hWnd);
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

void meduza::WinWindow::SwapBuffers()
{
	m_context->SwapBuffer();
}

void meduza::WinWindow::SetTitle(std::string a_title)
{
	m_title = a_title;
	SetWindowText(m_hWnd, m_title.c_str());
}

LRESULT __stdcall meduza::WinWindow::HandleMsgSetup(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{

	if (a_msg == WM_NCCREATE) {
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(a_lParam);
		WinWindow* const pWnd = static_cast<WinWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(a_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(a_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WinWindow::HandleMsgThunk));
		return pWnd->HandleMsg(a_hwnd, a_msg, a_wParam, a_lParam);
	}
	return DefWindowProc(a_hwnd, a_msg, a_wParam, a_lParam);
}

LRESULT __stdcall meduza::WinWindow::HandleMsgThunk(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{	//Get The window ptr stored in the API user data

	WinWindow* const pWnd = reinterpret_cast<WinWindow*>(GetWindowLongPtr(a_hwnd, GWLP_USERDATA));

	//Handle the messages!
	return pWnd->HandleMsg(a_hwnd, a_msg, a_wParam, a_lParam);
}

LRESULT meduza::WinWindow::HandleMsg(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	switch (a_msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(a_hwnd, a_msg, a_wParam, a_lParam);
}

meduza::WinWindow::WindowClass meduza::WinWindow::WindowClass::ms_wndClass;

meduza::WinWindow::WindowClass::WindowClass():
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
	UnregisterClass(ms_wndName, GetInstance());
}
