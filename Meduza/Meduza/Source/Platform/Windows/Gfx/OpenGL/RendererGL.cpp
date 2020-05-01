#include "mePch.h"

#include "Core.h"
#include "Drawable/Drawable.h"
#include "Util/MeduzaHelper.h"

#include <glad/glad.h>

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Gfx/OpenGL/ContextGL.h"

#include "Platform/Windows/Gfx/OpenGL/MeshGL.h"

const char* g_vertShader =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* g_fragShader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

meduza::renderer::RendererGL::RendererGL(Context& a_context)
{
    m_context = dynamic_cast<ContextGL*>(&a_context);

	int status = gladLoadGL(); 
    ME_GFX_ASSERT_M(status, "Glad not loaded");
	std::string version = (char*)(glGetString(GL_VERSION));
	printf("OpenGl version : %s \n", version.c_str());

    glViewport(0, 0, int(a_context.GetSize().m_x), int(a_context.GetSize().m_y));

	GenShaders();
}

meduza::renderer::RendererGL::~RendererGL()
{
}

void meduza::renderer::RendererGL::Clear(Colour a_colour)
{
	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b, a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererGL::Render()
{
	PopulateBuffers();

    if (m_quad != nullptr)
    {
        delete m_quad;
    }
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable* a_drawable)
{
    auto d = a_drawable->GetDrawData();

    std::vector<Vertex> vertices = {
        Vertex(0.5f + d->m_position.x ,  0.5f + d->m_position.y, 0.0f),  // top right
        Vertex(0.5f + d->m_position.x, -0.5f + d->m_position.y, 0.0f),  // bottom right
        Vertex(-0.5f + d->m_position.x, -0.5f + d->m_position.y, 0.0f),  // bottom left
        Vertex(-0.5f + d->m_position.x,  0.5f + +d->m_position.y, 0.0f),   // top left 
    };
    std::vector<int> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
    };

    m_quad = new MeshGL(0, vertices, indices, GL_LINE);
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*>)
{
 
}

void meduza::renderer::RendererGL::PreRender()
{

    if (m_quad != nullptr)
    {
        glUseProgram(m_shaderprogram);
        glBindVertexArray(m_quad->GetVAO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    PreRender();
}

void meduza::renderer::RendererGL::GenShaders()
{
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &g_vertShader, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &g_fragShader, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
   m_shaderprogram = glCreateProgram();
    glAttachShader(m_shaderprogram, vertexShader);
    glAttachShader(m_shaderprogram, fragmentShader);
    glLinkProgram(m_shaderprogram);
    // check for linking errors
    glGetProgramiv(m_shaderprogram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shaderprogram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
