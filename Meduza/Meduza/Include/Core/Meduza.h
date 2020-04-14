#pragma once

#include "MeduzaUtil.h"

namespace meduza
{
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
		bool IsWindowActive() const { return m_windowActive; }

	private:
		bool m_windowActive = false;
		renderer::Renderer* m_renderer;
	};
}