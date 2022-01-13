#pragma once
#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
	namespace Editor
	{
        enum class ProjectManagerState
        {
            InitialPage = 0,
            CreateNew,
            LoadProject,
            Disabled,

            LAST = LoadProject
        };

        class EditorProjectManager : public EditorWidget
        {
        public:
            EditorProjectManager();
            ~EditorProjectManager();

            void Draw() override;
            void SetEditorState(ProjectManagerState a_editorState, bool a_fromToolBar);

        private:
            void DrawInitialPage();
            void CreateNewProject();
            void LoadProject();

            bool m_opened;
            ProjectManagerState m_state;
            ProjectManagerState m_lastState;

            std::string m_newProjectName;
        };
	}
}