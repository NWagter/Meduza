#pragma once

namespace mr 
{
	class RenderLayer;
	class Window;
}

namespace me 
{

	class Meduza 
	{
	public:
		Meduza();
		~Meduza();

		void Update(float);

		void Clear(float[4]);
		void Render();

		bool IsActive();

	private:
		mr::Window* m_window;
		mr::RenderLayer* m_renderLayer;
	};
}