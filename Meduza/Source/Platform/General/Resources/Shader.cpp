#include "MePCH.h"
#include "Platform/General/Resources/Shader.h"

Me::Resources::GL::Shader::Shader(std::string a_shader) : ShaderBase(a_shader)
{
    m_source = Helper::GL::ShaderHelper::GetSources(a_shader);
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

bool ShaderDebug(unsigned int a_shader, std::string a_type)
{
    int success;
    std::vector<char> infoLog;
    glGetShaderiv(a_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(a_shader, 512, NULL, infoLog.data());
        std::string log(infoLog.data());
        std::cout << "ERROR::SHADER::" << a_type.c_str() << "::COMPILATION_FAILED\n" << log.c_str() << std::endl;
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
    ShaderDebug(vertexShader, "VERTEX");

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);
    ShaderDebug(fragmentShader, "PIXEL");

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    ShaderDebug(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	return shaderProgram;
}


void Me::Resources::GL::Shader::SetVec3(const std::string &a_name, const Math::Vec3 a_vec3)
{
    glUniform3f(glGetUniformLocation(m_program, a_name.c_str()), a_vec3.m_x, a_vec3.m_y, a_vec3.m_z);
}
void Me::Resources::GL::Shader::SetVec4(const std::string &a_name, const Math::Vec4 a_vec4)
{
    glUniform4f(glGetUniformLocation(m_program, a_name.c_str()), a_vec4.m_x, a_vec4.m_y, a_vec4.m_z, a_vec4.m_w);
}

void Me::Resources::GL::Shader::SetMat4(const std::string &a_name, const Math::Mat4 a_mat4, const bool a_transpose)
{
    Math::Mat4 glMat4 = a_mat4;

    glUniformMatrix4fv(glGetUniformLocation(m_program, a_name.c_str()), 1, a_transpose, &glMat4.m_mat[0][0]);
}