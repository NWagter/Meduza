#pragma once

namespace meduza
{
	namespace renderer
	{
		class Context
		{
		public:
			Context() = default;
			virtual ~Context() = default;

			virtual void SwapBuffers() = 0;
		};
	}
}