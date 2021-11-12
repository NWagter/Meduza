#pragma once

namespace Me {

	class Window;
	class SystemInitializer;

	namespace Event
	{
		class EventSystem;
	}

	namespace Debug
	{
		class MeduzaDebug;
	}

	struct RenderComponent;

	namespace Renderer
	{
		class RenderLayer;
	}

	namespace Scripting
	{
		class LuaScripting;
	}

	namespace Serialization
	{
		class Serializer;
	}

	namespace Editor
	{
		class EditorToolbar;
#ifdef PLATFORM_WINDOWS
		class EditorRenderer;
#endif
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

		inline static unsigned char GetEngineState() { return ms_engineState;}

	private:
		void Destroy();

		bool m_isRunning;
		static unsigned char ms_engineState;

		Debug::MeduzaDebug* m_meduzaDebugger;
		Renderer::RenderLayer* m_renderLayer;
		Serialization::Serializer* m_serializer;
		SystemInitializer* m_systemInitializer;
		Scripting::LuaScripting* m_luaScripting;

#ifdef PLATFORM_WINDOWS
		Editor::EditorRenderer* m_editor;
#endif
		Window* m_window;
		friend Editor::EditorToolbar;
	};
}