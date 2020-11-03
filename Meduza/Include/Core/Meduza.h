#pragma once
namespace Me {

	class Window;

	struct Renderable;

	namespace Renderer
	{
		class RenderLayer;
	}

	class Meduza
	{
	public:
		Meduza();
		~Meduza();
		
		inline bool IsRunning() { return m_isRunning; }

		void Clear();
		void Update();
		void Present();

		void Submit(Renderable*);
		void Submit(std::vector<Renderable*>);

	private:
		void Destroy();

		bool m_isRunning;
		Renderer::RenderLayer* m_renderLayer;
		Window* m_window;
	};
}