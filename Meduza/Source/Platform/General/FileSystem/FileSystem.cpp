#include "MePCH.h"

#include "Platform/General/FileSystem/FileSystem.h"

std::string Me::Files::FileSystem::ReadFile(std::string const& a_path)
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

std::string Me::Files::FileSystem::GetFromToken(std::string const& a_source, std::string const& a_token)
{
	std::string result = "";
	size_t typeTokenLenght = strlen(a_token.c_str());
	size_t pos = a_source.find(a_token.c_str(), 0);

	while (pos != std::string::npos)
	{
		size_t eol = a_source.find_first_of("\r\n", pos);
		ME_CORE_ASSERT_M(eol != std::string::npos, "Syntax Error");
		size_t begin = pos + typeTokenLenght + 1;
		result = a_source.substr(begin, eol - begin);
		break;
	}

	return result;
}

std::string Me::Files::FileSystem::GetFileName(std::string const& a_path)
{
	auto lastSlash = a_path.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = a_path.rfind('.');
	auto count = lastDot == std::string::npos ? a_path.size() - lastSlash : lastDot - lastSlash;

	return a_path.substr(lastSlash, count);
}

std::string Me::Files::FileSystem::GetFileExtention(std::string const& a_path)
{
	size_t i = a_path.rfind('.', a_path.length());
	if (i != std::string::npos) {
		return(a_path.substr(i + 1, a_path.length() - i));
	}

	return("");
}

bool Me::Files::FileSystem::DoesFileExist(std::string const& a_path)
{
	return std::filesystem::exists(a_path);
}

std::string Me::Files::FileSystem::CreateNewFile(std::string a_fileName, std::string a_path)
{
	std::string fullPath = a_path;
	fullPath.append("/");
	fullPath.append(a_fileName);

	std::filesystem::create_directories(a_path);
	std::ofstream newFile(fullPath);
	newFile.close();

	return fullPath;
}
void Me::Files::FileSystem::DeleteAsset(std::string a_path)
{
	if (!std::remove(a_path.c_str()))
	{
		ME_ASSERT_M(true, "Failed to delete %s \n", a_path.c_str());
	}
}