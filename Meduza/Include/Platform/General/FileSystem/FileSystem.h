#pragma once

namespace Me
{
	namespace Files
	{

		struct BrowseData
		{
			std::string m_path;
			std::vector<std::string> m_folders;
			std::vector<std::pair<std::string, std::string>> m_files;
		};

		class FileSystem
		{
		public:
			static std::string ReadFile(std::string const& a_path);
			static std::string GetFileName(std::string const& a_path);
			static std::string GetFileExtention(std::string const& a_path);
		};
	}
}
