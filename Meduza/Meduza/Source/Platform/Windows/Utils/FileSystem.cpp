#include "mePch.h"

#include "Core.h"
#include "Platform/Windows/Utils/FileSystem.h"

std::string meduza::utils::FileSystem::ReadFile(std::string a_path)
{
	std::string result;
	std::ifstream in(a_path, std::ios::in | std::ios::binary);

	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
	{
		ME_CORE_LOG("Could not find file at location : %s", a_path.c_str());
	}

	return result;
}

std::string meduza::utils::FileSystem::GetFileName(std::string a_path)
{
	auto lastSlash = a_path.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = a_path.rfind('.');
	auto count = lastDot == std::string::npos ? a_path.size() - lastSlash : lastDot - lastSlash;

	return a_path.substr(lastSlash, count);
}

std::string meduza::utils::FileSystem::GetFileExtention(std::string a_path)
{
	size_t i = a_path.rfind('.', a_path.length());
	if (i != std::string::npos) {
		return(a_path.substr(i + 1, a_path.length() - i));
	}

	return("");
}
