#include "MePCH.h"
#include "Platform/General/Resources/Shader.h"

Me::Resources::GL::Shader::Shader(std::string a_shader) : ShaderBase()
{
    m_source = Helper::GL::ShaderHelper::GetSources(a_shader);
    m_program = GenerateShader();

    glUseProgram(m_program);

    glUniform1i(glGetUniformLocation(m_program, "u_texture0"), 0);
    glUniform1i(glGetUniformLocation(m_program, "u_texture1"), 1);
    glUniform1i(glGetUniformLocation(m_program, "u_texture2"), 2);
    glUniform1i(glGetUniformLocation(m_program, "u_texture3"), 3);
    glUniform1i(glGetUniformLocation(m_program, "u_texture4"), 4);
    glUniform1i(glGetUniformLocation(m_program, "u_texture5"), 5);
    glUniform1i(glGetUniformLocation(m_program, "u_texture6"), 6);
    glUniform1i(glGetUniformLocation(m_program, "u_texture7"), 7);
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


#ifdef _DEBUG
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
#else
bool ShaderDebug(unsigned int, std::string)
{
    return true;
}
#endif

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

void Me::Resources::GL::Shader::SetFloat(std::string const& a_location, float const a_value)
{
    glUniform1f(glGetUniformLocation(m_program, a_location.c_str()), a_value);
}

void Me::Resources::GL::Shader::SetVec3(std::string const& a_location, Math::Vector3 const& a_vec3)
{
    glUniform3f(glGetUniformLocation(m_program, a_location.c_str()), a_vec3.m_x, a_vec3.m_y, a_vec3.m_z);
}
void Me::Resources::GL::Shader::SetVec4(std::string const& a_location, Math::Vector4 const& a_vec4)
{
    glUniform4f(glGetUniformLocation(m_program, a_location.c_str()), a_vec4.m_x, a_vec4.m_y, a_vec4.m_z, a_vec4.m_w);
}
void Me::Resources::GL::Shader::SetMat4(std::string const& a_location, Math::Matrix4 const& a_mat4, bool const a_transpose)
{
    Math::Matrix4 glMat4 = a_mat4;

    glUniformMatrix4fv(glGetUniformLocation(m_program, a_location.c_str()), 1, a_transpose, &glMat4.m_mat[0][0]);
}