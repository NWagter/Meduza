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

			WindowClass(WindowClass const&) = delete;
			WindowClass& operator=(WindowClass const&) = delete;
			static constexpr const char* ms_wndName = "WinWindow";
			static WindowClass ms_wndClass;
			HINSTANCE m_hInstance;

		};

	public:
		WindowsWindow(int const a_width, int const a_height, const char* a_title);
		virtual ~WindowsWindow();

		void ActiveCursor(bool a_showCursor) override;
		void Peek() override;
		void Quit() override;
		void SetContext(Renderer::ContextBase* a_context) override;

		void SetTitle(std::string const& a_title) override; 

		inline HWND GetWindowHandle() {return m_hWnd;}
	private:
		static LRESULT WINAPI HandleMsgSetup(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);
		static LRESULT WINAPI HandleMsgThunk(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);
		LRESULT HandleMsg(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);

		HWND m_hWnd;
	};
}