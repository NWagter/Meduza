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
			bool m_gjkDebugger = false;
			bool m_rayIntersections = false;
			bool m_showVertices = false;
			bool m_drawHitPoints = true;
			float m_scaleVertices = 0.2f;
			float m_timeScale = 1.0f;

			static Settings Empty()
			{
				Settings emptySettings;
				emptySettings.m_lineDebugger = false;
				emptySettings.m_collisionDebugger = false;
				emptySettings.m_showStats = false;
				emptySettings.m_debugCircle = false;
				emptySettings.m_gjkDebugger = false;
				emptySettings.m_rayIntersections = false;
				emptySettings.m_showVertices = false;
				emptySettings.m_drawHitPoints = false;
				return emptySettings;
			}
		};

		class MeduzaDebug
		{
		public:
			static Me::Debug::MeduzaDebug* CreateDebugger(Renderer::RenderLayer& a_renderLayer);
			~MeduzaDebug();
			static void RenderLine(Math::Vector3 const& a_start, Math::Vector3 const& a_end, Colour const a_colour = Colours::MAGENTA);
			static void RenderLine(Math::Vector3 const& a_start, Math::Vector3 const& a_direction, float const a_lenght, Colour const a_colour = Colours::MAGENTA);
			static void RenderCircle(Math::Matrix4 const& a_trans, float const a_radius, Colour const a_colour = Colours::MAGENTA);
			static void RenderSphere(Math::Matrix4 const& a_trans, float const a_radius, Colour const a_colour = Colours::MAGENTA);
			static Settings& GetDebuggingSettings();
		private:
			MeduzaDebug(Renderer::RenderLayer& a_renderLayer);

			static MeduzaDebug* ms_instance;
			Renderer::RenderLayer* m_renderLayer;
			Settings m_debuggingSettings;
		};
	}
}