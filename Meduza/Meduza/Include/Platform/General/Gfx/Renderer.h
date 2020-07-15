#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	class Camera;
	class Window;

	namespace drawable
	{
		class Drawable;
	}

	class Renderable;
	class Scene;

	struct Colour;

	namespace renderer
	{
		class Context;

		struct DrawStatistics
		{
			void Reset()
			{
				m_vertices = 0;
				m_drawables = 0;
				m_instances = 0;
				m_drawCalls = 0;
			}

			int m_vertices = 0;
			int m_drawables = 0;
			int m_instances = 0;
			int m_drawCalls = 0;
		};

		class Renderer
		{
		public:

			struct RendererData
			{
				renderer::Renderer* renderer = nullptr;
				Window* window = nullptr;
			};

			static RendererData* CreateRenderer(math::Vec2);
			static Renderer* SwitchAPI(Window&);
			virtual ~Renderer() = default;
			
			virtual void Clear(Colour) = 0;
			virtual void Render(const Camera&) = 0;

			virtual void Submit(Renderable&) = 0;
			virtual void Submit(Scene&) = 0;

			virtual DrawStatistics GetDrawStatistics() const = 0;
		};
	}
}