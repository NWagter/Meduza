#pragma once

#include "Gfx/Window.h"

class InputManager;


namespace mr {
	class Window;

	class WinWindow : public mr::Window {
	public:
		WinWindow(int, int, std::string);
		virtual ~WinWindow();

		WinWindow(const Window&) = delete;
		WinWindow& operator=(const Window&) = delete;

		virtual void SetTitle(const std::string) override;
		virtual bool Peek() override;
		virtual void Resize() override;

		inline const HWND GetHWND() { return m_windowHandle; }

		class WindowClass {
		public:
			static const char* GetName();
			static HINSTANCE GetInstance();
		private:
			WindowClass();
			~WindowClass();

			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;

			static constexpr const char* ms_wndClassName = "Window";
			static WindowClass ms_windowClass;
			HINSTANCE m_hInstance;
		};

	private:
		static LRESULT WINAPI HandleMsgSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT WINAPI HandleMsgThunk(HWND, UINT, WPARAM, LPARAM);
		// Handle messages, Keyboard and mouse input etc.
		LRESULT HandleMsg(HWND, UINT, WPARAM, LPARAM);

		HWND m_windowHandle;
	};
}