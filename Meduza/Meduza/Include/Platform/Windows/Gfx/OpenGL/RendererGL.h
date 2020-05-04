#pragma once

#include "Platform/General/Gfx/Renderer.h"

namespace meduza
{

	namespace renderer
	{
		class MeshGL;
		class Context;
		class ContextGL;

		class RendererGL : public Renderer
		{
		public:
			RendererGL(Context&);
			~RendererGL() override;

			void Clear(Colour) override;
			void Render() override;

			void Draw(drawable::Drawable*) override;
			void Submit(std::vector<drawable::Drawable*>) override;
		private:
			void PreRender();
			void PopulateBuffers();
			
			std::vector<DrawData> m_drawData;

			MeshGL* m_quad = nullptr;
			unsigned int m_shaderprogram = 0;

			ContextGL* m_context;

		};
	}

}