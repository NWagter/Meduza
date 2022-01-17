#include "MePCH.h"

#include "Platform/General/Editor/EditorProjectManager.h"

#include "Core/Project/ProjectManager.h"

#include "Platform/Windows/FileSystem/FileSystem.h"

Me::Editor::EditorProjectManager::EditorProjectManager()
{
	m_opened = false;
	m_state = ProjectManagerState::Disabled;

	if (Project::ProjectManager::GetLoadedProjectName().empty())
	{
		m_opened = true;
		m_state = ProjectManagerState::InitialPage;
	}
}

Me::Editor::EditorProjectManager::~EditorProjectManager()
{

}

void Me::Editor::EditorProjectManager::Draw()
{
	if (!m_opened)
	{
		return;
	}

	switch (m_state)
	{
	case Me::Editor::ProjectManagerState::InitialPage:
		DrawInitialPage();
		break;
	case Me::Editor::ProjectManagerState::CreateNew:
		CreateNewProject();
		break;
	case Me::Editor::ProjectManagerState::LoadProject:
		LoadProject();
		break;
	case Me::Editor::ProjectManagerState::Disabled:
		if (m_opened)
		{
			m_opened = false;
		}
		break;
	}
}

void Me::Editor::EditorProjectManager::DrawInitialPage()
{
	if (ImGui::Begin("Project Manager"))
	{
		if (ImGui::Button("Create New Project"))
		{
			m_lastState = m_state;
			m_state = ProjectManagerState::CreateNew;
			m_newProjectName = "NewProject";
		}
		if (ImGui::Button("Load Project"))
		{
			m_lastState = m_state;
			m_state = ProjectManagerState::LoadProject;
		}

		ImGui::End();
	}

}

void Me::Editor::EditorProjectManager::CreateNewProject()
{
	if (ImGui::Begin("Project Manager"))
	{
		std::string projectName;
		char buff[256] = {};
		strcpy(buff, m_newProjectName.c_str());
		ImGui::InputText("New Project Name", buff, IM_ARRAYSIZE(buff));
		m_newProjectName = buff;
		if (ImGui::Button("Create"))
		{
			//RemoveSpaces
			projectName = m_newProjectName;
			projectName.erase(remove_if(projectName.begin(), projectName.end(), isspace), projectName.end());

			Project::ProjectManager::GetProjectManager()->CreateProject(projectName);
			m_state = ProjectManagerState::Disabled;
			m_opened = false;
		}
		if (ImGui::Button("Return"))
		{
			m_state = m_lastState;
		}

		ImGui::End();
	}

}

void Me::Editor::EditorProjectManager::LoadProject()
{
	if (ImGui::Begin("Project Manager"))
	{
		//Find all available Projects
		Files::BrowseData data;
		Files::Windows::FileSystem::GetFilesOfType(data, Files::FileType::Project, true, "Projects");

		for (auto& file : data.m_files)
		{
			if(file->m_name._Starts_with(".Project"))
			{
				if(ImGui::Button(file->m_name.c_str()))
				{
					Project::ProjectManager::GetProjectManager()->LoadProject(file->m_path);
					m_state = ProjectManagerState::Disabled;
					m_opened = false;
				}
			}
		}

		if (ImGui::Button("Return"))
		{
			m_state = m_lastState;
		}
		ImGui::End();
	}

}


void Me::Editor::EditorProjectManager::SetEditorState(ProjectManagerState a_editorState, bool a_fromToolBar)
{
	if (a_fromToolBar && Project::ProjectManager::GetLoadedProjectName().empty())
	{
		return;
	}

	m_opened = true;
	m_state = a_editorState;

	if (a_fromToolBar)
	{
		m_lastState = ProjectManagerState::Disabled;
	}
}
