#include "mePch.h"

#pragma comment( lib, "Opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#include <glad/glad.h>

#include "Gfx/OpenGL/RendererOpenGL.h"
#include "Platform/Windows/WinWindow.h"

#include "Drawable/Drawable.h"
#include "Util/MeduzaHelper.h"

meduza::renderer::RendererOpenGL::RendererOpenGL(Window& a_window)
{
	printf("Create OpenGL Renderer \n");
	m_window = &a_window;

	CreateContext();

	int status = gladLoadGL();
	if (status != 0)
		static_assert(1, "Failed to initlize Glad!");

		std::string version = (char*)(glGetString(GL_VERSION));
	printf("OpenGl version : %s \n", version.c_str());

	glViewport(0, 0, int(m_window->GetSize().x), int(m_window->GetSize().y));
}

void meduza::renderer::RendererOpenGL::CreateContext()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 
		32,               
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0, 
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC hdc = GetDC(dynamic_cast<WinWindow*>(m_window)->GetHandle());

	int  windowPixelFormet;
	windowPixelFormet = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, windowPixelFormet, &pfd);

	HGLRC ourOpenGLRenderingContext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, ourOpenGLRenderingContext);
}

meduza::renderer::RendererOpenGL::~RendererOpenGL()
{
	printf("Delete OpenGL Renderer \n");

}

void meduza::renderer::RendererOpenGL::Clear(Colour a_colour)
{
	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b,a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererOpenGL::Submit(drawable::Drawable*)
{

	/*
	printf("\n  -------------------------------------------- \n");

	glm::vec2 pos = a_drawable->GetDrawData()->m_position;
	printf("drawable pos : %f - %f \n", pos.x, pos.y);
	
	printf("\n  -------------------------------------------- \n");
	*/
}

void meduza::renderer::RendererOpenGL::Submit(std::vector<drawable::Drawable*>)
{
/*
	unsigned int size = unsigned int(a_drawables.size());

	printf("\n Amount of Drawables : %i \n", size);


	printf("\n  -------------------------------------------- \n");
	for (auto d : a_drawables)
	{
		if (d->GetDrawData() != nullptr)
		{
			glm::vec3 pos = d->GetDrawData()->m_position;

			if (d->GetDrawType() == Type::Sprite)
			{
				printf("d=Sprite pos : %f - %f \n", pos.x, pos.y);
			}
			else if (d->GetDrawType() == Type::Model)
			{
				printf("d=Model pos : %f - %f - %f \n", pos.x, pos.y, pos.z);
			}
		}
		else
		{
			if (d->GetDrawType() == Type::None)
			{
				printf("d=None \n");
			}
		}
	}
	printf("\n  -------------------------------------------- \n");
	*/
}

void meduza::renderer::RendererOpenGL::Render()
{

	SwapBuffers(wglGetCurrentDC());
}
