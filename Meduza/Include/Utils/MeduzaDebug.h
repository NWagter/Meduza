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
			float m_debugLineLenght = 0.5f;
			bool m_lineDebugger = true;
			bool m_collisionDebugger = false;
			bool m_showStats = false;
			bool m_debugCircle = true;
		};

		class MeduzaDebug
		{
		public:
			static Me::Debug::MeduzaDebug* CreateDebugger(Renderer::RenderLayer& a_renderLayer);
			~MeduzaDebug();
			static void RenderLine(Math::Vector3 const& a_start, Math::Vector3 const& a_end, Colour const a_colour = Colours::MAGENTA);
			static void RenderLine(Math::Vector3& a_start, Math::Vector3& a_direction, float const a_lenght, Colour const a_colour = Colours::MAGENTA);
			static void RenderCircle(Math::Matrix4 const& a_trans, float const a_radius, Colour const a_colour = Colours::MAGENTA);
			static Settings& GetDebuggingSettings() { return ms_instance->m_debuggingSettings; }
		private:
			MeduzaDebug(Renderer::RenderLayer& a_renderLayer);

			static MeduzaDebug* ms_instance;
			Renderer::RenderLayer* m_renderLayer;
			Settings m_debuggingSettings;
		};
	}
}