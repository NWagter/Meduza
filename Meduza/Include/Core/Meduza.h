#pragma once
namespace Me {

	class Window;

	struct RenderComponent;

	namespace Renderer
	{
		class RenderLayer;
	}

	constexpr float CAM_WIDTH = 720;
	constexpr float CAM_HEIGHT = 680;

	class Meduza
	{
	public:
		Meduza();
		~Meduza();
		
		inline bool IsRunning() { return m_isRunning; }

		void Clear();
		void Update();
		void Present();

	private:
		void Destroy();

		bool m_isRunning;
		Renderer::RenderLayer* m_renderLayer;
		Window* m_window;
	};
}