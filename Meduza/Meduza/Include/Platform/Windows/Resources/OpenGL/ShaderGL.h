#pragma once

#include "Platform/General/Resources/Shader.h"
#include "Platform/General/Utils/ShaderUtils.h"

namespace meduza
{

	class ShaderGL : public Shader
	{
	public:
		ShaderGL(utils::ShaderSources);
		~ShaderGL() override;

		void Bind() override;
		void UnBind() override;

		void UploadUniformInt(std::string, int);

	private:
		utils::ShaderSources m_source;

		unsigned int GenerateShader();
		unsigned int m_program;
	};
}