#pragma once
#include "Platform/General/Window.h"

namespace Me
{
	class MacOsWindow : public Window
	{
	public:
		MacOsWindow(int, int, const char*);
		virtual ~MacOsWindow();

		void Peek() override;
		void Quit() override;
		void SetContext(Renderer::ContextBase*) override;

		void SetTitle(std::string) override; 

	};
}