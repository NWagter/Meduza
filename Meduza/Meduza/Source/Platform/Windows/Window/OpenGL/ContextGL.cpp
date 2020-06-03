#include "mePch.h"

#pragma comment( lib, "Opengl32.lib")
#pragma comment( lib, "glu32.lib")

#include "Math/MeduzaMath.h"

#include "Platform/Windows/Window/OpenGL/ContextGL.h"

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
	
	RECT rect;
	::GetClientRect(a_hwnd, &rect);

	m_size = math::Vec2(float(rect.right - rect.left), float(rect.bottom - rect.top));
}

meduza::renderer::ContextGL::~ContextGL()
{
	wglDeleteContext(m_glContext);
}

void meduza::renderer::ContextGL::SwapBuffer()
{

#if DOUBLE_BUFFER == 0
	glFlush();
	glFinish();
#elif DOUBLE_BUFFER == 1
	SwapBuffers(wglGetCurrentDC());
#endif
}

void meduza::renderer::ContextGL::Resize(math::Vec2 a_size)
{
	m_size = a_size;
	glViewport(0,0, int(a_size.m_x), int(a_size.m_y));
}

PIXELFORMATDESCRIPTOR meduza::renderer::ContextGL::CreateFormat()
{

	PIXELFORMATDESCRIPTOR pfd;
#if DOUBLE_BUFFER == 0
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
#elif DOUBLE_BUFFER == 1
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
#endif
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	return pfd;
}
