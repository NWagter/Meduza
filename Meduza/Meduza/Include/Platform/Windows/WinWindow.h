#pragma once

#include "Platform/General/Window.h"

namespace meduza
{
	class WinWindow : public Window
	{
	public:
		WinWindow(math::Vec2);
		~WinWindow() override;

		void Peek() override;
		void SwapBuffers() override;

		void SetTitle(std::string) override;

	private:

	};
}