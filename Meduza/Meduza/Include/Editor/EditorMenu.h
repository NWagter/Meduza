#pragma once

#include "IEditor.h"

namespace meduza
{
	class Window;

	namespace renderer
	{
		class Renderer;
	}

	namespace editor
	{
		class EditorStats;

		class EditorMenu : public IEditor
		{
		public:
			EditorMenu(renderer::Renderer&, Window&);
			~EditorMenu();

			// Inherited via IEditor
			void Update(const float) override;
			inline bool GetChangeAPI() const { return m_changeAPI; }
		private:
			void ChangeAPI();

			Window* m_window;
			renderer::Renderer* m_renderer;

			EditorStats* m_editorStats = nullptr;

			bool m_drawStats = false;
			std::vector<std::string> m_api;
			int m_currentAPI = 0;
			bool m_changeAPI = false;
		};
	}
}