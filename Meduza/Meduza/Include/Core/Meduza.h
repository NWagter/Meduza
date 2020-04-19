#pragma once

#include "MeduzaUtil.h"

#include "Drawable/Sprite.h"

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

		void Submit(drawable::Drawable*);

		void Submit(std::vector<drawable::Drawable*>);

		void Clear(Colour);
		void Render();


		void Peek();
		bool IsWindowActive() const;
		std::string GetWindowName();

		inline renderer::Renderer& GetGfx()
		{
			if (m_renderer != nullptr)
			{
				return *m_renderer;
			}

			static_assert(1, "NO RENDERER AVAILABLE");

			return *m_renderer;
		}

	private:
		bool m_windowActive = false;
		renderer::Renderer* m_renderer = nullptr;
		Window* m_window;
	};
}