#pragma once

#include "Platform/General/Window/Context.h"

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
			void Resize(math::Vec2) override;
			math::Vec2 GetSize() override { return m_size; };

		private:
			math::Vec2 m_size;
			PIXELFORMATDESCRIPTOR CreateFormat();
			PIXELFORMATDESCRIPTOR m_pFormat;
			HGLRC m_glContext;
		};
	}
}