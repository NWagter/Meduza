#include "cepch.h"
#include "Utils/FileSystem.h"

#include <fstream>

namespace ce
{
	bool FileSystem::ReadFileToString(const char* a_filepath, std::string& a_data)
	{
		std::ifstream is(a_filepath, std::ios::in | std::ios::binary);

		if (!is.is_open())
		{
			CE_CORE_WARN("Can't open file for reading: {0}", a_filepath);
			a_data = std::string();
			return false;
		}

		std::string data;
		is.seekg(0, std::ios::end);
		data.reserve(is.tellg());
		is.seekg(0, std::ios::beg);

		data.assign((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
		a_data = data;
		return true;
	}

	bool FileSystem::ReadFileToBuffer(const char* a_filepath, const char*& a_buffer, size_t a_bufferSize)
	{
		std::ifstream is(a_filepath, std::ios::in | std::ios::binary);

		if (!is.is_open())
		{
			CE_CORE_WARN("Can't open file for reading: {0}", a_filepath);
			a_buffer = nullptr;
			return false;
		}
		
		is.seekg(0, std::ios::beg);

		std::vector<char> buffer(a_bufferSize);
		if (is.read(buffer.data(), a_bufferSize))
		{
			a_buffer = buffer.data();
			return true;
		}

		a_buffer = nullptr;
		return false;
	}

	bool FileSystem::SaveFile(const char* a_filepath, const char*& a_data)
	{
		std::ofstream os(a_filepath, std::ofstream::out);

		if (!os.is_open())
		{
			CE_CORE_WARN("Couldn't open file for writing: {0}", a_filepath);
			return false;
		}

		//Write to file.
		os.write(a_data, strlen(a_data));

		return true;
	}
}