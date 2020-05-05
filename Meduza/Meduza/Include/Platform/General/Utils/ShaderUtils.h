#pragma once

namespace meduza
{
	class Shader;

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
		
		class ShaderData
		{
		public:
			virtual void SetInt(const Shader&, std::string, int) = 0;
			virtual void SetFloat(const Shader&, std::string, float) = 0;
			virtual void SetFloat2(const Shader&, std::string, float[2]) = 0;
			virtual void SetFloat3(const Shader&, std::string, float[3]) = 0;
			virtual void SetFloat4(const Shader&, std::string, float[4]) = 0;
		};
	}
}