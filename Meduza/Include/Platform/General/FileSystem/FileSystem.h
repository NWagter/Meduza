#pragma once

namespace Me
{
	namespace Resources
	{
		enum class ResourceType : uint8_t;
	}

	namespace Files
	{

		struct MeduzaFile
		{
			std::string m_path;
			std::string m_name;
			std::string m_extention;
			Resources::ResourceType m_type;

			MeduzaFile(std::string const& a_path, std::string const& a_name, std::string const& a_extention, Resources::ResourceType const a_type)
			{
				m_path = a_path;
				m_name = a_name;
				m_extention = a_extention;
				m_type = a_type;
			}
		};

		struct BrowseData
		{
			std::string m_path;
			std::vector<std::string> m_folders;
			std::vector<MeduzaFile*> m_files;

			void Clear()
			{
				m_path.clear(); 
				m_folders.clear();

				for (auto f : m_files)
				{
					delete f;
				}

				m_files.clear();
			}
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
