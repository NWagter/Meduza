#pragma once

#include "MeduzaUtil.h"

namespace meduza
{
	class Window;

	namespace renderer
	{
		class Renderer;
	}

	class Meduza 
	{
	public:
		Meduza(API);
		~Meduza();



		void Clear(Colour);
		void Render();


		void Peek();
		bool IsWindowActive() const;
		std::string GetWindowName();

	private:
		bool m_windowActive = false;
		renderer::Renderer* m_renderer = nullptr;
		Window* m_window;
	};
}