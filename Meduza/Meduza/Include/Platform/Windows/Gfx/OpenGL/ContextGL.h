#pragma once

#include "Platform/General/Context.h"

namespace meduza
{
	namespace renderer
	{
		class ContextGL : public Context
		{
		public:
			ContextGL();
			~ContextGL() override;

			void SwapBuffers() override;
		};
	}
}