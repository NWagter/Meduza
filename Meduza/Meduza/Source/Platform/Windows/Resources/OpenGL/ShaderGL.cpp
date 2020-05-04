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
