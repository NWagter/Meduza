#include "mePch.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include "Gfx/OpenGL/RendererOpenGL.h"
#include "Platform/Windows/WinWindow.h"

meduza::renderer::RendererOpenGL::RendererOpenGL(Window& a_window)
{
	printf("Create OpenGL Renderer \n");
	m_window = &a_window;

	CreateContext();
	glViewport(0, 0, int(m_window->GetSize().m_x), int(m_window->GetSize().m_y));
}

void meduza::renderer::RendererOpenGL::CreateContext()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
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
	std::string version = (char*)(glGetString(GL_VERSION));

	printf("OpenGl version : %s \n", version.c_str());
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

void meduza::renderer::RendererOpenGL::Draw(Sprite)
{

}

void meduza::renderer::RendererOpenGL::Draw(Mesh)
{
}

void meduza::renderer::RendererOpenGL::Draw(Text)
{
}

void meduza::renderer::RendererOpenGL::Render()
{
	SwapBuffers(wglGetCurrentDC());
}
