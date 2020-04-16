#pragma once

#include "Core/Window.h"

namespace meduza
{
	class WinWindow : public Window
	{
	public:
		WinWindow(int,int,std::string);
		~WinWindow() override;
		WinWindow(const Window&) = delete;
		WinWindow& operator=(const Window&) = delete;

		class WindowClass
		{
		public:
			inline static const char* GetName() { return ms_wndClassName; }
			inline static HINSTANCE GetInstance() { return ms_windowClass.m_hInstance; }
		private:
			WindowClass();
			~WindowClass();

			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;

			static constexpr const char* ms_wndClassName = "Window";
			static WindowClass ms_windowClass;
			HINSTANCE m_hInstance{ nullptr };
		};


		void Peek() override;
		bool WindowActive() override;

		void SetTitle(std::string) override;
		inline std::string GetTitle() override { return m_title; }

	private:
		static LRESULT WINAPI HandleMsgSetup(HWND, UINT, WPARAM, LPARAM);
		static LRESULT WINAPI HandleMsgThunk(HWND, UINT, WPARAM, LPARAM);

		// Handle messages, Keyboard and mouse input etc.
		LRESULT HandleMsg(HWND, UINT, WPARAM, LPARAM);

		HWND m_windowHandle;

		std::string m_title;
		bool m_windowActive = false;
	};
}