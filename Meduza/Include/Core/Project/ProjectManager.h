#pragma once

namespace Me
{
	namespace Project
	{
		class ProjectManager
		{
		public:
			static ProjectManager* CreateProjectManager();
			static ProjectManager* GetProjectManager()
			{
				return ms_instance;
			}

			static std::string const& GetAssetBrowserPath()
			{
				return ms_instance->m_assetBrowserBase;
			}
			static std::string const& GetLoadedProjectName()
			{
				return ms_instance->m_projectName;
			}
			~ProjectManager();
			
			void LoadProject(std::string const& a_path);
			void CreateProject(std::string const& a_name);

		private:
			ProjectManager();

			static ProjectManager* ms_instance;

			std::string m_projectName;
			std::string m_assetBrowserBase;
		};
	}
}