#pragma once

#include "Platform/General/Gfx/Renderer.h"

namespace meduza
{
	class Texture;
	class MeshGL;

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
			void CreateInstances();
			bool Cull(math::Vec2, math::Vec2);
			

			unsigned int m_textureId = 0;
			meduza::Texture* m_cachedTexture = nullptr;

			std::vector<DrawData*> m_drawData;

			std::vector<meduza::Texture*> m_textures;
			std::vector<InstanceData2D> m_instances = std::vector<InstanceData2D>(MAX_INSTANCES);

			unsigned int m_count = 0;
			unsigned int m_vbo = 0;
			unsigned int m_shaderID = 0;

			MeshGL* m_quad = nullptr;
			unsigned int m_shaderprogram = 0;

			ContextGL* m_context;

			math::Vec3 m_camPos = math::Vec3();
			glm::mat4 m_viewProjection = glm::mat4(1);
			DrawStatistics m_stats;
		};
	}

}