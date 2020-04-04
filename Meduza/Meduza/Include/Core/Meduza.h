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


	class Meduza 
	{
	public:
		Meduza();
		~Meduza();



		void Clear(float[]);

		void Render();
		bool IsWindowActive() const { return m_windowActive; }

	private:
		bool m_windowActive = false;
	};
}