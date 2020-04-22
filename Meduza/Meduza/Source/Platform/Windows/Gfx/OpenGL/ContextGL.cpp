#include "mePch.h"

#include "Platform/Windows/Gfx/OpenGL/ContextGL.h"

#include <glad/glad.h>

meduza::renderer::ContextGL::ContextGL(HWND a_hwnd)
{
	m_pFormat = CreateFormat();

	HDC ourWindowHandleToDeviceContext = GetDC(a_hwnd);

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &m_pFormat);
	SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &m_pFormat);

	m_glContext = wglCreateContext(ourWindowHandleToDeviceContext);
	wglMakeCurrent(ourWindowHandleToDeviceContext, m_glContext);
}

meduza::renderer::ContextGL::~ContextGL()
{
	wglDeleteContext(m_glContext);
}

void meduza::renderer::ContextGL::SwapBuffer()
{
	SwapBuffers(wglGetCurrentDC());
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
