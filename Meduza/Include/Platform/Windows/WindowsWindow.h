#pragma once
#include "Platform/General/Window.h"

namespace Me
{

	namespace Renderer
	{
		class WindowsContext;
	}

	class WindowsWindow : public Window
	{
	private:
		//Singleton for register and cleanup window class
		class WindowClass {
		public:
			static inline const char* GetName() { return ms_wndName; }
			static inline HINSTANCE GetInstance() { return ms_wndClass.m_hInstance; }

		private:
			WindowClass();
			~WindowClass();

			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* ms_wndName = "WinWindow";
			static WindowClass ms_wndClass;
			HINSTANCE m_hInstance;

		};

	public:
		WindowsWindow(int, int, const char*);
		virtual ~WindowsWindow();

		void Peek() override;
		void Quit() override;
		void SetContext(Renderer::ContextBase*) override;

		void SetTitle(std::string) override; 

		inline HWND GetWindowHandle() {return m_hWnd;}
	private:
		static LRESULT WINAPI HandleMsgSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT WINAPI HandleMsgThunk(HWND, UINT, WPARAM, LPARAM);
		LRESULT HandleMsg(HWND, UINT, WPARAM, LPARAM);

		HWND m_hWnd;
	};
}