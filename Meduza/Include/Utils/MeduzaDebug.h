#pragma once

namespace Me
{
	namespace Renderer
	{
		class RenderLayer;
	}

	namespace Debug
	{
		struct Settings
		{
			float m_debugLineLenght = 1.0f;
			bool m_lineDebugger = true;
			bool m_collisionDebugger = false;
			bool m_showStats = false;
			bool m_debugCircle = true;
		};

		class MeduzaDebug
		{
		public:
			static Me::Debug::MeduzaDebug* CreateDebugger(Renderer::RenderLayer&);
			~MeduzaDebug();
			static void RenderLine(Math::Vec3, Math::Vec3, Colour = Colours::MAGENTA);
			static void RenderLine(Math::Vec3, Math::Vec3, float, Colour = Colours::MAGENTA);
			static void RenderCircle(Math::Mat4&, float, Colour = Colours::MAGENTA);
			static Settings& GetDebuggingSettings() { return ms_instance->m_debuggingSettings; }
		private:
			MeduzaDebug(Renderer::RenderLayer&);

			static MeduzaDebug* ms_instance;
			Renderer::RenderLayer* m_renderLayer;
			Settings m_debuggingSettings;
		};
	}
}