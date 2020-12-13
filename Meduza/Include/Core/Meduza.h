#pragma once
namespace Me {

	class Window;

	struct RenderComponent;

	namespace Renderer
	{
		class RenderLayer;
	}

	class Meduza
	{
	public:
		Meduza(int,int);
		~Meduza();
		
		inline bool IsRunning() { return m_isRunning; }

		void Clear();
		void Update(float);
		void Present();

		void SetAppName(std::string);
		Math::Vec2 GetScreenSize();
	private:
		void Destroy();
		void CreatePrimitives();

		bool m_isRunning;
		Renderer::RenderLayer* m_renderLayer;
		Window* m_window;
	};
}