#pragma once

#include "Window.h"

class WinWindow : public Window {

public:
	WinWindow(int a_width, int a_height, const char* a_title);
	~WinWindow();

	class WindowClass {
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		~WindowClass();

		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
	private:
		static constexpr const char* ms_wndClassName = "Window";
		static WindowClass ms_windowClass;
		HINSTANCE m_hInstance;
	};
	virtual void SetTitle(const std::string a_newTitle) override;

	virtual bool PeekMsg() override;
	const HWND GetWindowHandle();

private:

	static LRESULT WINAPI HandleMsgSetup(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);
	static LRESULT WINAPI HandleMsgThunk(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);
	// Handle messages, Keyboard and mouse input etc.
	LRESULT HandleMsg(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);

	HWND m_hwnd;
};