#pragma once

#include "MeduzaHelper.h"


namespace meduza
{
	namespace renderer
	{
		class Renderer;
	}

	class Meduza 
	{
	public:
		Meduza();
		~Meduza();



		void Clear(float[]);

		void Render();
		bool IsWindowActive() const { return m_windowActive; }

	private:
		bool m_windowActive = true;
		renderer::Renderer* m_renderer;
	};
}