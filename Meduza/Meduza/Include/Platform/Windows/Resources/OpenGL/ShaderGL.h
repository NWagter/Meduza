#pragma once

#include "Platform/General/Resources/Shader.h"
#include "Platform/General/Utils/ShaderUtils.h"

namespace meduza
{

	class ShaderGL : public Shader
	{
	public:
		ShaderGL() = default;
		ShaderGL(utils::ShaderSources);
		ShaderGL(utils::ShaderSources, ShaderLayout);
		~ShaderGL() override;

		void Reload() override;

		void Bind() override;
		void UnBind() override;

		void UploadUniformInt(std::string, int);
		void UploadUniformFloat(std::string, float);

		void UploadUniformVec2(std::string, float[2]);
		void UploadUniformVec3(std::string, float[3]);
		void UploadUniformVec4(std::string, float[4]);

		void UploadUniformVec2(std::string, glm::vec2);
		void UploadUniformVec3(std::string, glm::vec3);
		void UploadUniformVec4(std::string, glm::vec4);

		void UploadUniformMat4(std::string, glm::mat4);

	private:
		utils::ShaderSources m_source;

		unsigned int GenerateShader();
		unsigned int m_program;
		bool m_generated = false;
	};
}