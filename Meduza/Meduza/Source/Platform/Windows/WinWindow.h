#pragma once

#include "Gfx/Window.h"

class InputManager;

namespace cr {

	class WinWindow : public Window {
	public:
		WinWindow(int, int, std::string);
		virtual ~WinWindow();
		WinWindow(const Window&) = delete;
		WinWindow& operator=(const Window&) = delete;

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


		virtual void SetTitle(const std::string) override;
		virtual bool Peak() override;
		virtual void Resize() override; // give new size

		inline const HWND GetHWND() { return m_windowHandle; }
		inline const bool GetResize() { return m_resizeWindow; }
	private:
		static LRESULT WINAPI HandleMsgSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT WINAPI HandleMsgThunk(HWND, UINT, WPARAM, LPARAM);
		// Handle messages, Keyboard and mouse input etc.
		LRESULT HandleMsg(HWND, UINT, WPARAM, LPARAM);

		HWND m_windowHandle;

		bool m_resizeWindow;

		InputManager* m_inputManager = nullptr;
	};
}