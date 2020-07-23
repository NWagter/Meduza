#pragma once

#include "Platform/General/Gfx/Renderer.h"

namespace meduza
{
	class Texture;
	class MeshGL;
	class ShaderGL;
	class Material;

	namespace renderer
	{
		class Context;
		class ContextGL;

		class RendererGL : public Renderer
		{
		public:
			RendererGL(Context&);
			~RendererGL() override;

			void Clear(Colour) override;
			void Render(const Camera&) override;

			void Submit(Renderable&) override;
			void Submit(Scene&) override;

			DrawStatistics GetDrawStatistics() const override;
		private:
			void PreRender();
			void PopulateBuffers();
			bool Cull(math::Vec2, math::Vec2);

			std::vector<float> m_c;

			ShaderGL* m_lastShader = nullptr;

			std::vector<Renderable*> m_renderables;

			ContextGL* m_context;

			math::Vec3 m_camPos = math::Vec3();
			glm::mat4 m_viewProjection = glm::mat4(1);
			DrawStatistics m_stats;
		};
	}

}