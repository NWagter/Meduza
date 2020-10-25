#include "MePCH.h"
#include "Platform/Linux/Helper/ShaderReader.h"

#include "Platform/General/FileSystem/FileSystem.h"

Me::Helper::GL::ShaderSources Me::Helper::GL::ShaderUtils::GetSources(std::string a_vertPath, std::string a_fragPath)
{
	ShaderSources source;

	source.m_vertexSource = File::FileSystem::ReadFile(a_vertPath);
	source.m_pixelSource = File::FileSystem::ReadFile(a_fragPath);

	source.m_shaderName = File::FileSystem::GetFileName(a_vertPath);
	return source;
}
Me::Helper::GL::ShaderSources Me::Helper::GL::ShaderUtils::GetSources(std::string a_path)
{
	ShaderSources source;
	
	std::string shaderSource = File::FileSystem::ReadFile(a_path);

	const char* typeToken = "#type";
	size_t typeTokenLenght = strlen(typeToken);
	size_t pos = shaderSource.find(typeToken, 0);

	while (pos != std::string::npos)
	{
		size_t eol = shaderSource.find_first_of("\r\n", pos);
		ME_CORE_ASSERT_M(eol != std::string::npos, "Syntax Error");
		size_t begin = pos + typeTokenLenght + 1;
		std::string type = shaderSource.substr(begin, eol - begin);
		ME_CORE_ASSERT_M(type == "Vertex" || type == "Fragment" || type == "Pixel", "Invalid shader type make sure to use Vertex, Fragment or Pixel as a type");

		size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
		pos = shaderSource.find(typeToken, nextLinePos);

		if (type == "Vertex")
		{
			source.m_vertexSource = shaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSource.size() - 1 : nextLinePos));
		}
		else if (type == "Fragment" || type == "Pixel")
		{
			source.m_pixelSource = shaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSource.size() - 1 : nextLinePos));
		}

	}
    
	source.m_shaderName = File::FileSystem::GetFileName(a_path);

	return source;
}