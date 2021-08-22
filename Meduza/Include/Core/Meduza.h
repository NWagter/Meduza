#pragma once
namespace Me {

	class Window;

	struct RenderComponent;

	namespace Renderer
	{
		class RenderLayer;
	}

	namespace Editor
	{
		class EditorRenderer;
	}

	class Meduza
	{
	public:
		Meduza(int,int, GFX_API);
		~Meduza();
		
		inline bool IsRunning() { return m_isRunning; }

		void Clear();
		void Update(float);
		void Present();

		void SetAppName(std::string);
		Math::Vec2 GetScreenSize();
	private:
		void Destroy();

		bool m_isRunning;
		Renderer::RenderLayer* m_renderLayer;
		Editor::EditorRenderer* m_editor;
		Window* m_window;
	};
}