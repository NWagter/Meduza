#include "mePch.h"

#include "Platform/Windows/Utils/OpenGL/ShaderUtilsGL.h"

#include "Platform/Windows/Resources/OpenGL/ShaderGL.h"

void meduza::utils::ShaderDataGl::SetInt(const Shader& a_shader, std::string a_uniform, int a_value)
{
	auto s = dynamic_cast<const ShaderGL&>(a_shader);
	s.UploadUniformInt(a_uniform, a_value);
}

void meduza::utils::ShaderDataGl::SetFloat(const Shader& a_shader, std::string a_uniform, float a_value)
{
	auto s = dynamic_cast<const ShaderGL&>(a_shader);
	s.UploadUniformFloat(a_uniform, a_value);
}

void meduza::utils::ShaderDataGl::SetFloat2(const Shader& a_shader, std::string a_uniform, float a_value[2])
{
	auto s = dynamic_cast<const ShaderGL&>(a_shader);
	s.UploadUniformVec2(a_uniform, a_value);
}

void meduza::utils::ShaderDataGl::SetFloat3(const Shader& a_shader, std::string a_uniform, float a_value[3])
{
	auto s = dynamic_cast<const ShaderGL&>(a_shader);
	s.UploadUniformVec3(a_uniform, a_value);
}

void meduza::utils::ShaderDataGl::SetFloat4(const Shader& a_shader, std::string a_uniform, float a_value[4])
{
	auto s = dynamic_cast<const ShaderGL&>(a_shader);
	s.UploadUniformVec4(a_uniform, a_value);
}
