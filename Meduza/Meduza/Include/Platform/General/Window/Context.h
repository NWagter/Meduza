#pragma once

#define DOUBLE_BUFFER 1

namespace meduza
{
	namespace math
	{
		class Vec2;
	}

	namespace renderer
	{
		class Context
		{
		public:
			Context() = default;
			virtual ~Context() = default;

			virtual void SwapBuffer() = 0;
			virtual void Resize(math::Vec2) = 0;
			virtual math::Vec2 GetSize() = 0;
		};
	}
}