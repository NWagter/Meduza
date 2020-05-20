#pragma once

#include "Platform/General/Gfx/Renderer.h"

namespace meduza
{
	class Texture;

	namespace renderer
	{
		class MeshGL;
		class Context;
		class ContextGL;

		struct Instance
		{
			Instance()
			{
				m_data.resize(MAX_INSTANCES);
			}
			std::vector<InstanceData2D> m_data;
			unsigned int m_count = 0;
			unsigned int m_vbo;
			unsigned int m_shaderId = 0;
		};

		class RendererGL : public Renderer
		{
		public:
			RendererGL(Context&);
			~RendererGL() override;

			void Clear(Colour) override;
			void Render(const Camera&) override;

			void Draw(drawable::Drawable*) override;
			void Submit(std::vector<drawable::Drawable*>) override;
			DrawStatistics GetDrawStatistics() const override;
		private:
			void PreRender();
			void PopulateBuffers();
			

			unsigned int m_textureId = 0;
			meduza::Texture* m_cachedTexture = nullptr;
			unsigned int m_instanceID = 0;
			std::vector<Instance> m_instances;

			MeshGL* m_quad = nullptr;
			unsigned int m_shaderprogram = 0;

			ContextGL* m_context;

			glm::mat4 m_viewProjection = glm::mat4(1);
			DrawStatistics m_stats;
		};
	}

}