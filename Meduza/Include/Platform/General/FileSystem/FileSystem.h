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
			static std::string ReadFile(std::string);
			static std::string GetFileName(std::string);
			static std::string GetFileExtention(std::string);
		};
	}
}
