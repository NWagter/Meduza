#include "mePch.h"

#include "MeduzaUtil.h"
#include <glad/glad.h>

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/General/Window.h"

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

meduza::renderer::RendererGL::RendererGL()
{
	int status = gladLoadGL(); 
	assertm(status, "Glad not loaded");

	std::string version = (char*)(glGetString(GL_VERSION));
	printf("OpenGl version : %s \n", version.c_str());

	glViewport(0, 0, int(Renderer::GetWindow().GetSize().m_x), int(Renderer::GetWindow().GetSize().m_y));


	Test();
}

meduza::renderer::RendererGL::~RendererGL()
{
	delete Renderer::m_window;
}

void meduza::renderer::RendererGL::Clear(Colour a_colour)
{
#ifdef DEV
    if (MeduzaHelper::ms_optick)
    {
        OPTICK_GPU_EVENT("Clear");
    }
#endif

	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b, a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererGL::SwapBuffers()
{
	PopulateBuffers();

	Renderer::GetWindow().SwapBuffers();
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable*)
{
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*>)
{
}

void meduza::renderer::RendererGL::PreRender()
{
    glUseProgram(m_shaderprogram);
    m_quad->EnableMode();
    glBindVertexArray(m_quad->GetVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    PreRender();
#ifdef DEV
    if (MeduzaHelper::ms_optick)
    {
        OPTICK_GPU_EVENT("Render Frame");
    }
#endif
}

void meduza::renderer::RendererGL::Test()
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

    std::vector<Vertex> vertices = {
        Vertex(0.5f,  0.5f, 0.0f),  // top right
        Vertex(0.5f, -0.5f, 0.0f),  // bottom right
        Vertex(-0.5f, -0.5f, 0.0f),  // bottom left
        Vertex(-0.5f,  0.5f, 0.0f),   // top left 
    };
    std::vector<int> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
    };

    m_quad = new MeshGL(0, vertices, indices, GL_LINE);
}
