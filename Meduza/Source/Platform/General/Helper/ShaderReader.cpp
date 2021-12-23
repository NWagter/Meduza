#include "MePCH.h"
#include "Platform/General/Helper/ShaderReader.h"

#include "Platform/General/FileSystem/FileSystem.h"

Me::Helper::GL::ShaderSources Me::Helper::GL::ShaderHelper::GetSources(std::string a_vertexShader, std::string a_pixelShader)
{
	ShaderSources source;
	
	source.m_vertexSource = Files::FileSystem::ReadFile(a_vertexShader);
	source.m_pixelSource = Files::FileSystem::ReadFile(a_pixelShader);

	source.m_shaderName = Files::FileSystem::GetFileName(a_vertexShader);
	return source;
}
Me::Helper::GL::ShaderSources Me::Helper::GL::ShaderHelper::GetSources(std::string a_shader)
{
	ShaderSources source;
	
	std::string shaderSource = Files::FileSystem::ReadFile(a_shader);

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
    
	source.m_shaderName = Files::FileSystem::GetFileName(a_shader);

	return source;
}