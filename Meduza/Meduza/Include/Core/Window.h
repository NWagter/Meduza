#pragma once


#include "MeduzaUtil.h"

namespace meduza
{
	class Window
	{
	public:
		static Window* CreateNewWindow(int,int);
		virtual ~Window() = default;

		virtual void Peek() = 0;

		virtual void SetTitle(std::string) = 0;
		virtual std::string GetTitle() = 0;
		
		virtual bool WindowActive() = 0;
	};
}