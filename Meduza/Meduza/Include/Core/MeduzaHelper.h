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

	struct Material
	{
		unsigned int m_shaderId = 0;

		float m_albedo[4] = { 1,1,1,1 };
	};


	struct Drawable
	{
		//Position
		//Size
		//Rotation
	};

	struct Sprite : Drawable
	{
		//Texture
		//VBO Quad
		Material m_material;
	};

	struct Mesh : Drawable
	{
		//Texture
		//VBO
		Material m_material;
	};

	struct Text : Drawable
	{
		//Font
		//Albedo

	};
}
