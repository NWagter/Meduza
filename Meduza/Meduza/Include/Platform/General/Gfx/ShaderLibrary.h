#pragma once

#include "Platform/General/Resources/Shader.h"

namespace meduza
{

	class ShaderLibrary
	{
	public:
		ShaderLibrary();

		static Shader* LoadShader(std::string, std::string);
		static Shader* LoadShader(std::string);

		static Shader* GetShader(std::string);
		static Shader* GetShader(unsigned int);

		static bool UnLoadShader(std::string);
		static bool UnLoadShader(unsigned int, bool = true);

	private:
		static ShaderLibrary* m_instance;
		std::unordered_map<unsigned int, Shader*> m_shaders;
	};
}