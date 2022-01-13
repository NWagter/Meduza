#pragma once

namespace Me
{
	namespace Project
	{
		class ProjectManager
		{
		public:
			ProjectManager();
			~ProjectManager();

			void LoadProject(std::string const& a_path);
			void CreateProject(std::string const& a_name);

		private:

			std::string m_projectName;
		};
	}
}