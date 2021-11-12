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
			bool m_lineDebugger = false;
			bool m_collisionDebugger = false;
		};

		class MeduzaDebug
		{
		public:
			static Me::Debug::MeduzaDebug* CreateDebugger(Renderer::RenderLayer&);
			~MeduzaDebug();
			static void RenderLine(Math::Vec3, Math::Vec3);
			static void RenderLine(Math::Vec3, Math::Vec3, float);
			static Settings& GetDebuggingSettings() { return ms_instance->m_debuggingSettings; }
		private:
			MeduzaDebug(Renderer::RenderLayer&);

			static MeduzaDebug* ms_instance;
			Renderer::RenderLayer* m_renderLayer;
			Settings m_debuggingSettings;
		};
	}
}