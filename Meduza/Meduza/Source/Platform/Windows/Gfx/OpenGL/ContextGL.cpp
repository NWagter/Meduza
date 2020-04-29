#include "mePch.h"

#pragma comment( lib, "Opengl32.lib")
#pragma comment( lib, "glu32.lib")

#include "Math/MeduzaMath.h"
#include "Util/MeduzaHelper.h"

#include "Platform/Windows/Gfx/OpenGL/ContextGL.h"

#include <glad/glad.h>

meduza::renderer::ContextGL::ContextGL(HWND a_hwnd)
{

	
	m_pFormat = CreateFormat();

	HDC dContext = GetDC(a_hwnd);

	int  wPixFormat;
	wPixFormat = ChoosePixelFormat(dContext, &m_pFormat);
	SetPixelFormat(dContext, wPixFormat, &m_pFormat);

	m_glContext = wglCreateContext(dContext);
	wglMakeCurrent(dContext, m_glContext);
}

meduza::renderer::ContextGL::~ContextGL()
{
	wglDeleteContext(m_glContext);
}

void meduza::renderer::ContextGL::SwapBuffer()
{
	if (MeduzaHelper::ms_optick)
	{
		OPTICK_GPU_EVENT("Present");
	}

	SwapBuffers(wglGetCurrentDC());
}

void meduza::renderer::ContextGL::Resize(math::Vec2 a_size)
{
	m_size = a_size;

	glViewport(0,0, int(a_size.m_x), int(a_size.m_y));
}

PIXELFORMATDESCRIPTOR meduza::renderer::ContextGL::CreateFormat()
{

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
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

	return pfd;
}
