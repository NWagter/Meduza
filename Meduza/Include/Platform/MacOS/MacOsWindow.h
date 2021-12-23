#pragma once
#include "Platform/General/Window.h"

namespace Me
{
	class MacOsWindow : public Window
	{
	public:
		MacOsWindow(int const a_width,  int const a_height, const char* a_title);
		virtual ~MacOsWindow();

		void ActiveCursor(bool) override;
		void Peek() override;
		void Quit() override;
		void SetContext(Renderer::ContextBase* a_context) override;

		void SetTitle(std::string const& a_title) override;

	};
}