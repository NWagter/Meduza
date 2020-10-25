#include "MePCH.h"
#include "Platform/Linux/Resources/Shader.h"

Me::Resources::GL::Shader::Shader(std::string a_vShader, std::string a_pShader)
{
    m_source = Helper::GL::GetSources(a_vShader, a_pShader)
    m_program = GenerateShader();
}

Me::Resources::GL::Shader::Shader(std::string a_shader)
{
    m_source = Helper::GL::GetSources(a_shader)
    m_program = GenerateShader();
}

Me::Resources::GL::Shader::~Shader()
{
    glDeleteShader(m_program);
}

void Me::Resources::GL::Shader::Reload()
{
    Unload();
}

void Me::Resources::GL::Shader::Unload()
{
    glDeleteShader(m_program);
}

void Me::Resources::GL::Shader::Bind()
{
    glUseProgram(m_program);
}

void Me::Resources::GL::Shader::UnBind()
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

unsigned int Me::Resources::GL::Shader::GenerateShader()
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