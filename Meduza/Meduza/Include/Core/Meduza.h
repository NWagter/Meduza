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



		void Clear(float[4]);

		void Render();
		bool IsWindowActive() const { return m_windowActive; }

	private:
		bool m_windowActive = false;
		renderer::Renderer* m_renderer;
	};
}