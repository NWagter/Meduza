#pragma once

#include "IEditor.h"

namespace meduza
{
	namespace renderer
	{
		class Renderer;
	}

	namespace editor
	{
		class EditorStats : public IEditor
		{
		public:
			EditorStats(renderer::Renderer&);
			~EditorStats();

			void Update(const float) override;

		private:
			renderer::Renderer* m_renderer;
			float m_deltaSecond = 0;
			float m_timer = 1.1f; // 1.1f to init correctly first time
		};
	}
}