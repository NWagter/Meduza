#pragma once

namespace meduza
{
	enum class API
	{
		OpenGL,
#ifdef PLATFORM_PI
		OpenGLES2,
#elif PLATFORM_WINDOWS
		DirectX12
#endif // PLATFORM_WINDOWS

	};


	struct Drawable
	{

	};

	struct Sprite : Drawable
	{

	};

	struct Mesh : Drawable
	{

	};

	struct Text : Drawable
	{

	};
}
