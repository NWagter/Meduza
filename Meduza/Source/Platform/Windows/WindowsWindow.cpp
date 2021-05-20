#include "MePCH.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Platform/General/ContextBase.h"

#include "Platform/General/Events/EventSystem.h"

Me::WindowsWindow::WindowsWindow(int a_w, int a_h, const char* a_title) : Window(a_w, a_h, a_title)
{
	m_active = true;

	ME_LOG("Window Created : %s \n", m_title);

	RECT wr;
	wr.left = 0;
	wr.right = int(m_size.m_x) + wr.left;
	wr.top = 0;
	wr.bottom = int(m_size.m_y) + wr.top;
	
	m_hWnd = CreateWindow(WindowClass::GetName(), m_title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	ActiveCursor(false);
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}

Me::WindowsWindow::~WindowsWindow()
{
}

void Me::WindowsWindow::ActiveCursor(bool a_active)
{
	ShowCursor(a_active);	
}

void Me::WindowsWindow::Peek()
{
	MSG msg;
	m_eventSystem->Clear();

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

void Me::WindowsWindow::SetTitle(std::string a_title)
{
	std::string title = a_title;
	title.append(" | Windows");
	SetWindowText(m_hWnd, title.c_str());
	ME_GFX_LOG("Change name of window to : %s \n", title.c_str());
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
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam); // NOLINT
LRESULT Me::WindowsWindow::HandleMsg(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	// ImGui Input Handles
	if (ImGui_ImplWin32_WndProcHandler(a_hwnd, a_msg, a_wParam, a_lParam) != 0)
	{
		return 1;
	}

	switch (a_msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
// ---- Mouse
	case WM_MOUSEMOVE: {
		const auto mousePos = MAKEPOINTS(a_lParam);
		Math::Vec2 mPos;
		mPos.m_x = static_cast<float>(mousePos.x) - (m_size.m_x / 2);
		mPos.m_y = (m_size.m_y / 2) - static_cast<float>(mousePos.y);

		if (mousePos.x >= 0 && float(mousePos.x) < m_size.m_x && mousePos.y >= 0 && float(mousePos.y) < m_size.m_y) {
			m_eventSystem->OnMouseMove(mPos);
			SetCapture(a_hwnd);
		}
		else {
			if ((a_wParam & (MK_LBUTTON | MK_RBUTTON)) != 0u) {
				m_eventSystem->OnMouseMove(mPos);
			}
			else {
				ReleaseCapture();
			}
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		m_eventSystem->OnMouseEvent(Event::MouseButton::LButton, Event::MouseEvent::MouseDown);
		break;
	}
	case WM_LBUTTONUP:
	{
		m_eventSystem->OnMouseEvent(Event::MouseButton::LButton, Event::MouseEvent::MouseUp);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		m_eventSystem->OnMouseEvent(Event::MouseButton::RButton, Event::MouseEvent::MouseDown);
		break;
	}
	case WM_RBUTTONUP:
	{
		m_eventSystem->OnMouseEvent(Event::MouseButton::RButton, Event::MouseEvent::MouseUp);
		break;
	}
// ---- Keyboard
	case WM_SYSKEYDOWN:
	{
		case WM_KEYDOWN:
		{
			Event::KeyCode key = static_cast<Event::KeyCode>(a_wParam);
			m_eventSystem->OnKeyEvent(key ,Event::KeyState::KeyDown);
		}
		break;
	}
	case WM_SYSKEYUP:
	{
		case WM_KEYUP:
		{
			Event::KeyCode key = static_cast<Event::KeyCode>(a_wParam);
			m_eventSystem->OnKeyEvent(key ,Event::KeyState::KeyUp);
		}
		break;
	}


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