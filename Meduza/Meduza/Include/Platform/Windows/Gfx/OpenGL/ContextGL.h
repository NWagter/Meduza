#pragma once

#include "Platform/General/Context.h"

namespace meduza
{
	namespace renderer
	{
		class ContextGL : public Context
		{
		public:
			ContextGL(HWND);
			~ContextGL() override;

			void SwapBuffer() override;

		private:

			PIXELFORMATDESCRIPTOR CreateFormat();
			PIXELFORMATDESCRIPTOR m_pFormat;
			HGLRC m_glContext;
		};
	}
}