#pragma once

namespace meduza
{
	namespace utils
	{
		class FileSystem
		{
		public:
			static std::string ReadFile(std::string);
			static std::string GetFileName(std::string);
			static std::string GetFileExtention(std::string);
		};
	}
}
