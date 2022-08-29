#include "MePCH.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Platform/General/ContextBase.h"
#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/Events/EventSystem.h"

Me::WindowsWindow::WindowsWindow(int const a_width, int const a_height, const char* a_title) : Window(a_width, a_height, a_title)
{
	m_eventSystem = nullptr;
	m_context = nullptr;
	m_active = true;

	ME_LOG("Window Created : %s \n", m_title);

	DWORD wFlags = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_BORDER | WS_SIZEBOX;
	RECT wr = {0,0, a_width, a_height};
	AdjustWindowRect(&wr, wFlags, true);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	// Center the window within the screen. Clamp to 0, 0 for the top-left corner.
	int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
	int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);

	m_hWnd = CreateWindow(WindowClass::GetName(), 
		m_title,
		wFlags,
		windowX,
		windowY,
		windowWidth,
		windowHeight,
		nullptr, 
		nullptr, 
		WindowClass::GetInstance(),
		this);

	ActiveCursor(true);
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}

Me::WindowsWindow::~WindowsWindow()
{
}

void Me::WindowsWindow::ActiveCursor(bool a_showCursor)
{
	ShowCursor(a_showCursor);
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

void Me::WindowsWindow::SetTitle(std::string const& a_title)
{
	std::string api;

	switch (Renderer::RenderLayer::GetAPI())
	{
	case Me::GFX_API::OpenGL:
		api = "OpenGL";
		break;
	case Me::GFX_API::DX12:
		api = "DX12";
		break;
	default:
		api = "Unknown";
		break;
	}

	std::string title = a_title;
	title.append(" | Windows | " + api);
	SetWindowText(m_hWnd, title.c_str());
	ME_GFX_LOG("Change name of window to : %s \n", title.c_str());
} 

void Me::WindowsWindow::SetContext(Renderer::ContextBase* a_context)
{
	m_context = a_context;
}

LRESULT __stdcall Me::WindowsWindow::HandleMsgSetup(HWND const a_hwnd, UINT const a_msg, WPARAM const a_wParam, LPARAM const a_lParam)
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
	case WM_SIZE :
	{ 

		int width = LOWORD(a_lParam);
		int height = HIWORD(a_lParam);
		OnResize(width, height);

		if(m_context != nullptr)
		{
			m_context->Resize(width,height);
			m_eventSystem->SetScreenSize(m_size);
		}

		break;
	}
	case WM_KILLFOCUS: 
	{
		if(m_eventSystem != nullptr)
		{
			m_eventSystem->Clear();
		}
		break;
	}
// ---- Mouse
	case WM_MOUSEMOVE: 
	{
		const auto mousePos = MAKEPOINTS(a_lParam);
		float const mouseX = static_cast<float>(mousePos.x) - (m_size.m_x * .5f);
		float const mouseY = (m_size.m_y * .5f) - static_cast<float>(mousePos.y);

		Math::Vector2 mPos
		{
			Math::Clamp(-m_halfSize.m_x, m_halfSize.m_x, mouseX),
			Math::Clamp(-m_halfSize.m_y, m_halfSize.m_y, mouseY)
		};

		m_eventSystem->OnMouseMove(mPos);
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
	case WM_MOUSEWHEEL:
	{
		float const mouseDelta = GET_WHEEL_DELTA_WPARAM(a_wParam);

		if (mouseDelta < 0.0f)
		{
			// Scroll Down
			m_eventSystem->OnMouseScroll(false);
		}
		else if (mouseDelta > 0.0f)
		{
			// Scroll Up
			m_eventSystem->OnMouseScroll(true);
		}

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