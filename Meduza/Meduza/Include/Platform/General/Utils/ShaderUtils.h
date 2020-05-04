#pragma once

namespace meduza
{
	namespace utils
	{
		struct ShaderSources
		{
			std::string m_vertexSource;
			std::string m_pixelSource;
			std::string m_shaderName;
		};

		class ShaderUtils
		{
		public:
			static ShaderSources GetSources(std::string, std::string);
			static ShaderSources GetSources(std::string);
			static unsigned int GetHashedID(std::string);
		};
	}
}