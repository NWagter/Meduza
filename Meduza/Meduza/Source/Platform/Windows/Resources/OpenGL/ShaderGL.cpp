#include "mePch.h"

#include <glad/glad.h>
#include "Platform/Windows/Resources/OpenGL/ShaderGL.h"

meduza::ShaderGL::ShaderGL(utils::ShaderSources a_source) : Shader(utils::ShaderUtils::GetHashedID(a_source.m_shaderName))
{
    m_source = a_source;

	m_program = GenerateShader();
}

meduza::ShaderGL::~ShaderGL()
{
    glDeleteShader(m_program);
}

void meduza::ShaderGL::Bind()
{
    glUseProgram(m_program);
}

void meduza::ShaderGL::UnBind()
{
    glUseProgram(0);
}

void meduza::ShaderGL::UploadUniformInt(std::string a_uniform, int a_value)
{
    unsigned int location = glGetUniformLocation(m_program, a_uniform.c_str());

    glUniform1i(location, a_value);
}

void meduza::ShaderGL::UploadUniformFloat(std::string a_uniform, float a_value)
{
    unsigned int location = glGetUniformLocation(m_program, a_uniform.c_str());

    glUniform1f(location, a_value);
}

void meduza::ShaderGL::UploadUniformVec2(std::string a_uniform, float a_value[2])
{
    unsigned int location = glGetUniformLocation(m_program, a_uniform.c_str());

    glUniform2f(location, a_value[0], a_value[1]);
}

void meduza::ShaderGL::UploadUniformVec3(std::string a_uniform, float a_value[3])
{
    unsigned int location = glGetUniformLocation(m_program, a_uniform.c_str());

    glUniform3f(location, a_value[0], a_value[1], a_value[2]);
}

void meduza::ShaderGL::UploadUniformVec4(std::string a_uniform, float a_value[4])
{
    unsigned int location = glGetUniformLocation(m_program, a_uniform.c_str());

    glUniform4f(location, a_value[0], a_value[1], a_value[2], a_value[3]);
}

bool ShaderDebug(unsigned int a_shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(a_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(a_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    return true;
}

unsigned int meduza::ShaderGL::GenerateShader()
{
    const char* vertSource = m_source.m_vertexSource.c_str();
    const char* fragSource = m_source.m_pixelSource.c_str();

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);
    ShaderDebug(vertexShader);

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);
    ShaderDebug(fragmentShader);

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    ShaderDebug(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	return shaderProgram;
}
